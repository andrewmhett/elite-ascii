#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <iostream>
#include <string.h>
#include "graphics.h"
#include "fileio.h"
using namespace std;

vector<Button> buttons;
WINDOW* main_window;
int button_index=0;
int width;
int height;

void clear_screen(){
	button_index=0;
	buttons.clear();
	clear();
	update_screen(main_window);
	box(main_window,0,0);
	update_screen(main_window);
}

void load_save_game_menu(){
	
}

void start_new_game(){
	NewSave(buttons[0].text);
}

void exit_game(){
	endwin();
	exit(0);
}

void load_main_menu();

void create_new_game(){
	clear_screen();
	add_button(width/2,(height/2)-(height/10),width*0.6,height/8,"",main_window,2,buttons,start_new_game,true);
	add_button(width/2,(height/2)+(height/10),width*0.6,height/8,"Back",main_window,2,buttons,load_main_menu);
	attron(COLOR_PAIR(2));
	draw_string(startx+width/2,starty+(height/2)-(height/10),"Enter save name here",main_window);
	attroff(COLOR_PAIR(2));
	update_screen(main_window);
}

void load_main_menu(){
	clear_screen();
	attron(COLOR_PAIR(1));
	main_window=new_window();
	width=0;
	height=0;
	startx++;
	starty++;
	getmaxyx(main_window, height, width);
	width-=2;
	height-=2;
	box(main_window,0,0);
	attron(A_STANDOUT);
	draw_string(startx+width/2,starty+height/7," Elite: Ascii ",main_window);
	attroff(A_STANDOUT);
	add_button(width/2,height/3,width*0.6,height/8,"Load Saved Game",main_window,2,buttons,load_save_game_menu);
	add_button(width/2,height/2,width*0.6,height/8,"New Game",main_window,2,buttons,create_new_game);
	add_button(width/2,height-height/3,width*0.6,height/8,"Exit",main_window,2,buttons,exit_game);
	update_screen(main_window);
}

int main(){
	initscr();
	start_color();
	noecho();
	cbreak();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_WHITE,COLOR_BLUE);
	load_main_menu();
	unsigned char in;
	while (1){
		in = getch();
		switch(in){
			case '\033':
				getch();
				switch (getch()){
					//down arrow
					case 'B':
						if (button_index+1<buttons.size()){
							buttons[button_index].selected=false;
							button_index++;
							buttons[button_index].selected=true;
							draw_buttons(buttons);
							update_screen(main_window);
						}
						break;
					//up arrow
					case 'A':
						if (button_index-1>=0){
							buttons[button_index].selected=false;
							button_index--;
							buttons[button_index].selected=true;
							draw_buttons(buttons);
							update_screen(main_window);
						}
						break;
				}
				break;
			//enter
			case 10:
				buttons[button_index].callback();
				break;
			//backspace
			case 127:
				if (buttons[button_index].text_entry){
					if (buttons[button_index].text.length()>0){
						buttons[button_index].text=buttons[button_index].text.substr(0,buttons[button_index].text.length()-1);
						buttons[button_index].draw();
						update_screen(main_window);
					}
				}
				break;
			//all other characters
			default:
				if (buttons[button_index].text_entry){
					buttons[button_index].text+=in;
					buttons[button_index].draw();
					update_screen(main_window);
				}
				break;
		}
	}
	endwin();
	return 0;
}
