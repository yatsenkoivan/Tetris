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
		int type = rand()%4;
		type = 3;
		switch(type){
			case 0:
				/*[][][][]*/
				for (int ind=0; ind<size; ind++){
					y[ind] = 0;
					x[ind] = w/2+ind*2-1;
				}
				break;
			case 1:
				/*[]
				  [][][]*/
				y[0] = 0;
				x[0] = w/2 + 2 - 1;
				for (int ind=1; ind<size; ind++){
					y[ind] = 1;
					x[ind] = w/2+ind*2-1;
				}
				break;
			case 2:
				/*    []
				  [][][]*/
				y[0] = 0;
				x[0] = w/2 + (size-1)*2 - 1;
				for (int ind=1; ind<size; ind++){
					y[ind] = 1;
					x[ind] = w/2+ind*2 - 1;
				}
				break;
			case 3:
				/*[][]
				  [][]*/
				for (int ind=0; ind<size/2; ind++){
					y[ind] = 0;
					x[ind] = w/2 + ind*2 - 1;
				}
				for (int ind=size/2; ind<size; ind++){
					y[ind] = 1;
					x[ind] = w/2 + (ind-size/2)*2 - 1;
				}
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
		//false - game over, otherwise true
		bool NewFigure(){
			for (int col=0; col<w; col++){
				if (arr[0][col] != void_symbol) return false;
			}
			
			current = new Figure(w/2);
			
			ShowFigure();
			
			return true;
		}
		void ShowFigure(){
			for (int ind=0; ind<Figure::size; ind++){
				setcursor(current->x[ind]+1, current->y[ind]+1);
				std::cout << "[]";
			}
		}
		void Press(char move){
			int shift=0;
			switch(move){
				case 'a':
				case 'A':
					shift-=2;
					break;
				case 'd':
				case 'D':
					shift+=2;
					break;
			}
			int* x = new int[Figure::size];
			int* y = new int[Figure::size];

			for (int ind=0; ind<Figure::size; ind++){
				x[ind] = current->x[ind]+shift;
				y[ind] = current->y[ind];
			}
			
			for (int ind=0; ind<Figure::size; ind++){
				if (x[ind] < 0 || x[ind]+1 >= w) return;
				if (arr[y[ind]][x[ind]] != Board::void_symbol) return;
			}
			
			ReshowFigure(shift);
			
			delete[] x;
			delete[] y;
		}
		void Fall(){
			int* x = new int[Figure::size];
			int* y = new int[Figure::size];

			for (int ind=0; ind<Figure::size; ind++){
				x[ind] = current->x[ind];
				y[ind] = current->y[ind]+1;
			}
			
			for (int ind=0; ind<Figure::size; ind++){
				if (y[ind] >= h || arr[y[ind]][x[ind]] != Board::void_symbol){
					SaveFigure();
					BurnLines();
					NewFigure();
					return;
				}
			}
			
			ReshowFigure(1, false);
			
			delete[] x;
			delete[] y;
		}
		void ReshowFigure(int shift, bool x=true){
			for (int ind=0; ind<Figure::size; ind++){
				setcursor(current->x[ind]+1, current->y[ind]+1);
				std::cout << arr[current->y[ind]][current->x[ind]] << arr[current->y[ind]][current->x[ind]+1];
				if (x) current->x[ind]+=shift;
				else current->y[ind]+=shift;
			}
			for (int ind=0; ind<Figure::size; ind++){
				setcursor(current->x[ind]+1, current->y[ind]+1);
				std::cout << "[]";
			}
		}
		void SaveFigure(){
			for (int ind=0; ind<Figure::size; ind++){
				arr[current->y[ind]][current->x[ind]] = '[';
				arr[current->y[ind]][current->x[ind]+1] = ']';
			}
			delete current;
			current = nullptr;
		}
		void BurnLines(){
			bool burn;
			bool shift;
			for (int row=h-1; row>=0; row--){
				burn = true;
				shift = true;
				for (int col=0; col<w; col++){
					if (arr[row][col] == Board::void_symbol){
						burn = false;
					}
					else{
						shift = false;
					}
				}
				if (burn){
					for (int col=0; col<w; col++){
						arr[row][col] = Board::void_symbol;
					}
				}
				if (shift && row > 0){
					for (int col=0; col<w; col++){
						std::swap(arr[row][col], arr[row-1][col]);
					}
				}
			}
		}
};
char Board::void_symbol = ' ';

