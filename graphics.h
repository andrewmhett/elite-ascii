#include <sys/ioctl.h>
using namespace std;

int framerate=30;

void update_screen(WINDOW* window){
	wrefresh(window);
	refresh();
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

void draw_string(int x, int y, string str, WINDOW* window){
	mvprintw(y,x-str.length()/2,str.data());
	update_screen(window);
}
