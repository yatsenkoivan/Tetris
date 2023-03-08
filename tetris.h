#pragma once

#include <vector>
#include <iostream>
#include <windows.h>
#include <algorithm>
using std::cout;
using std::endl;


HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
char SQUARE = 219; //symbol 'white square', will be used to show figures.
const int board_x = 10;
const int board_y = 20;
char Board[board_y][board_x];
int Board_colors[board_y][board_x]{};

enum Colours{
	blue=9, green, light_blue, red, pink, light_yellow, yellow=6, white=7
};

class Figure{
	public:
		int color;
		std::vector<int> x;
		std::vector<int> y;
		
		Figure(){
			x = {-1,-1,-1,-1};
			y = {-1,-1,-1,-1};
			color = 0;
		}
		
		void set(){
			int random_color = rand()%7+9;
			//int random_color = 14;
			if (random_color == 15) color = yellow;
			else color = random_color;
			
			int pos = 0;
			switch(color){
				case blue:
					x[pos] = 4;
					y[pos] = 0;
					pos++;
					for (int i=4; i<7; i++){
						x[pos] = i;
						y[pos] = 1;
						pos++;
					}
					break;
				case green:
					for (int i=4; i<6; i++){
						x[pos] = i;
						y[pos] = 1;
						pos++;
					}
					for (int i=5; i<7; i++){
						x[pos] = i;
						y[pos] = 0;
						pos++;
					}
					break;
				case light_blue:
					for (int i=4; i<8; i++){
						x[pos] = i;
						y[pos] = 0;
						pos++;
					}
					break;
				case red:
					for (int i=4; i<6; i++){
						x[pos] = i;
						y[pos] = 0;
						pos++;
					}
					for (int i=5; i<7; i++){
						x[pos] = i;
						y[pos] = 1;
						pos++;
					}
					break;
				case pink:
					x[pos] = 5;
					y[pos] = 0;
					pos++;
					for (int i=4; i<7; i++){
						x[pos] = i;
						y[pos] = 1;
						pos++;
					}
					break;
				case light_yellow:
					for (int i=4; i<6; i++){
						x[pos] = i;
						y[pos] = 0;
						pos++;
					}
					for (int i=4; i<6; i++){
						x[pos] = i;
						y[pos] = 1;
						pos++;
					}
					break;
				case yellow:
					x[pos] = 6;
					y[pos] = 0;
					pos++;
					for (int i=4; i<7; i++){
						x[pos] = i;
						y[pos] = 1;
						pos++;
					}
					break;
			}
		}
		void rotate();
		void move(char dir);
};


//set color of text
void set_color(int color_id){
	SetConsoleTextAttribute(h, color_id);
}
//welcome page
void welcome(){
	cout << "AD to move\n";
	cout << "Q to rotate\n";
	system("pause");
}
//show board
void show_board(Figure& f){
	bool flag = false; //figure part
	cout << '+';
	for (int col=0; col<board_x; col++)cout << '-';
	cout << '+' << endl;
	for (int row=0; row<board_y; row++){
		cout << '|';
		for (int col=0; col<board_x; col++){
			flag = false;
			for (int i=0; i<4; i++){
				if (f.y[i] == row && f.x[i] == col){
					set_color(f.color);
					cout << SQUARE;
					set_color(white);
					flag = true;
					break;
				}
			}
			if (!flag){
				set_color(Board_colors[row][col]);
				cout << Board[row][col];
				set_color(white);
			}
		}
		cout << '|' << endl;
	}
	cout << '+';
	for (int col=0; col<board_x; col++)cout << '-';
	cout << '+' << endl;
}

//set board
void start(){
	for (int row=0; row<board_y; row++){
		for (int col=0; col<board_x; col++) Board[row][col] = ' ';
	}
}


//Figure functions:
void Figure::move(char dir){
	bool flag = true; //ability to move
	
	int change_x=0;
	int change_y=0;
	
	switch(dir){
		case 'a':
			change_x = -1;
			change_y = 0;
			break;
		case 'd':
			change_x = 1;
			change_y = 0;
			break;
		case 's':
			change_x = 0;
			change_y = 1;
			break;
	}
	//checking ability to move figure
	for (int i=0; i<4; i++){
		if (x[i] + change_x >= board_x || x[i] + change_x < 0){
			flag = false;
			break;
		}
		if (y[i] + change_y >= board_y || y[i] + change_y < 0){
			flag = false;
			break;
		}
		if (std::find(x.begin(), x.end(), x[i]+change_x) == x.end()){
			if (Board[y[i]][x[i]+change_x] == SQUARE){
				flag = false;
				break;
			}
		}
		if (std::find(y.begin(), y.end(), y[i]+change_y) == y.end()){
			if (Board[y[i]+change_y][x[i]] == SQUARE){
				flag = false;
				break;
			}
		}
	}
	
	bool figure_set = false;
	if (flag){
		for (int i=0; i<4; i++){
			x[i] += change_x;
			y[i] += change_y;
		}
	}else{
		for (int i=0; i<4; i++){
			if (y[i] == board_y-1){
				figure_set = true;
				break;
			}
			if (std::find(y.begin(), y.end(), y[i]+1) == y.end()){
				if (Board[y[i]+1][x[i]] == SQUARE){
					figure_set = true;
					break;
				}
			}
		}
		if (figure_set){
			for (int i=0; i<4; i++){
				Board[y[i]][x[i]] = SQUARE;
				Board_colors[y[i]][x[i]] = color;
			}
			color = 0;
		}
	}
	
	
	
}


