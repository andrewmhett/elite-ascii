#include <sys/ioctl.h>
#include <thread>
#include <vector>
#include <unistd.h>
using namespace std;

int framerate=30;

void update_screen(WINDOW* window){
	wrefresh(window);
	refresh();
}

void draw_string(int x, int y, string str, WINDOW* window){
	mvprintw(y,x-str.length()/2,str.data());
}

class Button{
	public:
		int x1, x2, y1, y2;
		string text;
		WINDOW* window;
		int color;
		bool selected=false;
		Button(int a, int b, int c, int d, string txt, WINDOW* win, int color_pair){
			x1=a;
			x2=b;
			y1=c;
			y2=d;
			text=txt;
			window=win;
			color=color_pair;
		}
		void draw(){
			mvhline(y1, x1, 0, x2-x1);
			mvhline(y2, x1, 0, x2-x1);
			mvvline(y1, x1, 0, y2-y1);
			mvvline(y1, x2, 0, y2-y1);
			mvaddch(y1, x1, ACS_ULCORNER);
		 	mvaddch(y2, x1, ACS_LLCORNER);
			mvaddch(y1, x2, ACS_URCORNER);
		    	mvaddch(y2, x2, ACS_LRCORNER);
			if (selected){
				attron(COLOR_PAIR(color));
			}
			for (int x=x1+1;x<x2;x++){
				for (int y=y1+1;y<y2;y++){
					mvaddch(y,x,' ');
				}
			}
			draw_string(x1+((x2-x1)/2),y1+((y2-y1)/2),text,window);
			attroff(COLOR_PAIR(color));
		}
};

void add_button(int x, int y, int width, int height, string text, WINDOW* window, int color_pair, vector<Button> &button_list){
	Button new_button = Button(x-(width/2),x+(width/2),y-(height/2),y+(height/2),text,window,color_pair);
	if (button_list.empty()){
		new_button.selected=true;
	}
	new_button.draw();
	button_list.push_back(new_button);
}

void draw_buttons(vector<Button> button_list){
	for (vector<Button>::iterator it = button_list.begin(); it != button_list.end(); ++it){
		Button button = *it;
		button.draw();
	}
}

WINDOW* new_window(){
	curs_set(0);
	struct winsize size;
	ioctl( 0, TIOCGWINSZ, (char *) &size );
	WINDOW* new_win;
	if (size.ws_row<size.ws_col/2){
		int startx=(size.ws_col/2)-(size.ws_row);
		new_win = newwin(size.ws_row, size.ws_row*2, 0, startx);
	}else{
		int starty=(size.ws_row)-(size.ws_col/2);
		new_win = newwin(size.ws_col/2, size.ws_col, starty/2, 0);
	}
	return new_win;
}
