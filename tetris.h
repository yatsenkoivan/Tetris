#pragma once
#include <iostream>
#include <windows.h>
#include <time.h>

void setcursor(short x, short y) { 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}


struct Figure{
	static int size;
	int* x;
	int* y;
	Figure(int w){
		x = new int[size];
		y = new int[size];
		srand(time(0));
		int type = rand()%3;
		switch(type){
			case 0:
				/*[][][][]*/
				for (int ind=0; ind<size; ind++){
					y[ind] = 0;
					x[ind] = w/2+ind*2;
				}
				break;
			case 1:
				/*[]
				  [][][]*/
				y[0] = 0;
				x[0] = w/2 + 2;
				for (int ind=1; ind<size; ind++){
					y[ind] = 1;
					x[ind] = w/2+ind*2;
				}
				break;
			case 2:
				/*    []
				  [][][]*/
				y[0] = 0;
				x[0] = w/2 + (size-1)*2;
				for (int ind=1; ind<size; ind++){
					y[ind] = 1;
					x[ind] = w/2+ind*2;
				}
				break;
		}
	}
	~Figure(){
		delete[] x;
		delete[] y;
	}
};
int Figure::size = 4;


class Board{
	private:
		int w;
		int h;
		char** arr;
		Figure* current;
	public:
		static char void_symbol;
		
		Board(int w, int h) : w{w*2}, h{h} {
			arr = new char*[this->h];
			for (int row=0; row<this->h; row++){
				arr[row] = new char[this->w];
				for (int col=0; col<this->w; col++) arr[row][col] = void_symbol;
			}
			current = nullptr;
		}
		Board() : Board(10, 20) {}
		~Board(){
			for (int row=0; row<h; row++){
				delete[] arr[row];
			}
			delete[] arr;
		}
		void Show(){
			system("cls");
			std::cout << '+';
			for (int col=0; col<w; col++) std::cout << '-';
			std::cout << '+' << std::endl;
			for (int row=0; row<h; row++){
				std::cout << '|';
				for (int col=0; col<w; col++) std::cout << arr[row][col];
				std::cout << '|' << std::endl;
			}
			std::cout << '+';
			for (int col=0; col<w; col++) std::cout << '-';
			std::cout << '+' << std::endl;
		}
		//true - game over, otherwise false
		bool NewFigure(){
			for (int col=0; col<w; col++){
				if (arr[0][col] != void_symbol) return true;
			}
			
			current = new Figure(w/2);
			
			ShowFigure();
			
			return false;
		}
		void ShowFigure(){
			for (int ind=0; ind<Figure::size; ind++){
				setcursor(current->x[ind]+1, current->y[ind]+1);
				std::cout << "[]";
			}
		}
		void Move(char move){
			
			switch(move){
				case 'a':
				case 'A':
					
					break;
				case 'd':
				case 'D':
					
					break;
			}
		}
};
char Board::void_symbol = ' ';

