#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <iostream>
#include <string.h>
#include "graphics.h"
using namespace std;

int main(){
	initscr();
	cbreak();
	refresh();
	WINDOW* main_window=new_window();
	int width=0;
	int height=0;
	getmaxyx(main_window, height, width);
	box(main_window,0,0);
	attron(A_STANDOUT);
	draw_string(width/2,height/4," Elite: Ascii ",main_window);
	while (1){
	}
	endwin();
	return 0;
}
