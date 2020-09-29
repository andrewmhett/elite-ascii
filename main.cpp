#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <iostream>
#include <string.h>
#include "graphics.h"
using namespace std;

vector<Button> buttons;

int button_index=0;

void load_saved_game(){}

void create_new_game(){}

void exit_game(){
	endwin();
	exit(0);
}

int main(){
	initscr();
	start_color();
	noecho();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_WHITE,COLOR_BLUE);
	attron(COLOR_PAIR(1));
	cbreak();
	refresh();
	WINDOW* main_window=new_window();
	int width=0;
	int height=0;
	startx++;
	starty++;
	getmaxyx(main_window, height, width);
	width-=2;
	height-=2;
	box(main_window,0,0);
	attron(A_STANDOUT);
	draw_string(startx+width/2,starty+height/7," Elite: Ascii ",main_window);
	attroff(A_STANDOUT);
	add_button(width/2,height/3,width*0.6,height/8,"Load Saved Game",main_window,2,buttons,load_saved_game);
	add_button(width/2,height/2,width*0.6,height/8,"New Game",main_window,2,buttons,create_new_game);
	add_button(width/2,height-height/3,width*0.6,height/8,"Exit",main_window,2,buttons,exit_game);
	update_screen(main_window);
	while (1){
		switch(getch()){
			//down arrow
			case 66:
				if (button_index+1<buttons.size()){
					buttons[button_index].selected=false;
					button_index++;
					buttons[button_index].selected=true;
					draw_buttons(buttons);
					update_screen(main_window);
				}
				break;
			//up arrow
			case 65:
				if (button_index-1>=0){
					buttons[button_index].selected=false;
					button_index--;
					buttons[button_index].selected=true;
					draw_buttons(buttons);
					update_screen(main_window);
				}
				break;
			//right arrow
			case 67:
				break;
			//left arrow
			case 68:
				break;
			//enter
			case 10:
				buttons[button_index].callback();
				break;
		}
	}
	endwin();
	return 0;
}
