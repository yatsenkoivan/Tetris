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
		int type = rand()%7;
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
				break;
			case 4:
				/*  [][]
				  [][]  */
				for (int ind=0; ind<size/2; ind++){
					y[ind] = 1;
					x[ind] = w/2 + 2*ind - 1;
				}
				for (int ind=size/2; ind<size; ind++){
					y[ind] = 0;
					x[ind] = w/2 + 2*(ind-size/2+1) - 1;
				}
				break;
			case 5:
				/*  []
				  [][][]*/
			  	y[0] = 0;
			  	x[0] = w/2 + 4 - 1;
			  	for (int ind=1; ind<size; ind++){
					y[ind] = 1;
					x[ind] = w/2 + ind*2 - 1;
			  	}
			  	break;
			case 6:
				/*[][]
				    [][]*/
				for (int ind=0; ind<size/2; ind++){
					y[ind] = 0;
					x[ind] = w/2 + 2*ind - 1;
				}
				for (int ind=size/2; ind<size; ind++){
					y[ind] = 1;
					x[ind] = w/2 + 2*(ind-size/2+1) - 1;
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
		Figure* nextFigure;
	public:
		static char void_symbol;
		
		Board(int w, int h) : w{w*2}, h{h} {
			arr = new char*[this->h];
			for (int row=0; row<this->h; row++){
				arr[row] = new char[this->w];
				for (int col=0; col<this->w; col++) arr[row][col] = void_symbol;
			}
			current = nullptr;
			nextFigure = new Figure(this->w/2);
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
			ShowNext();
		}
		void ShowNext(){
			setcursor(w+2, 0);
			for (int col=0; col<Figure::size*2+4; col++) std::cout << '-';
			std::cout << '+';
			for (int row=0; row<4; row++){
				setcursor(w+2+Figure::size*2+4, row+1);
				std::cout << '|';
			}
			setcursor(w+2, 5);
			for (int col=0; col<Figure::size*2+4; col++) std::cout << '-';
			std::cout << '+';
		}
		//false - game over, otherwise true
		bool NewFigure(){
			for (int col=0; col<w; col++){
				if (arr[0][col] != void_symbol) return false;
			}
			
			current = nextFigure;
			nextFigure = new Figure(w/2);
			
			ShowFigure();
			ShowNextFigure();
			
			return true;
		}
		void ShowFigure(){
			for (int ind=0; ind<Figure::size; ind++){
				setcursor(current->x[ind]+1, current->y[ind]+1);
				std::cout << "[]";
			}
		}
		void ShowNextFigure(){
			for (int row=0; row<4; row++){
				setcursor(w+2, row+1);
				for (int col=0; col<Figure::size*2+2; col++){
					std::cout << ' ';
				}
			}
			for (int ind=0; ind<Figure::size; ind++){
				setcursor(nextFigure->x[ind]-(w/4+2-1) + w+6, nextFigure->y[ind]+2);
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
				case 'r':
				case 'R':
					Rotate();
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
			
			ReshowFigure(current->x, current->y, x, y);
			
			delete[] x;
			delete[] y;
		}
		void Rotate(){
			int mid = Figure::size/2;
			int midx = current->x[mid];
			int midy = current->y[mid];
			int x[Figure::size];
			int y[Figure::size];
			for (int ind=0; ind<Figure::size; ind++){
				x[ind] = current->x[ind];
				y[ind] = current->y[ind];
				
				
				if (x[ind] != midx && y[ind] == midy){
					y[ind] = midy - (midx - x[ind])/2;
					x[ind] = midx;
					continue;
				}
				if (x[ind] == midx && y[ind] != midy){
					x[ind] = midx + (midy - y[ind])*2;
					y[ind] = midy;
					continue;
				}
				if (x[ind] != midx && y[ind] != midy){
					if (x[ind] < midx){
						if (y[ind] < midy){
							x[ind] = midx + midx-x[ind];
						}
						else{
							y[ind] = midy + midy-y[ind];
						}
					}
					else{
						if (y[ind] < midy){
							y[ind] = midy + midy-y[ind];
						}
						else{
							x[ind] = midx + midx-x[ind];
						}
					}
				}
			}
			for (int ind=0; ind<Figure::size; ind++){
				if (x[ind] < 0 || x[ind]+1 >= w) return;
				if (y[ind] < 0 || y[ind]+1 >= w) return;
				if (arr[y[ind]][x[ind]] != Board::void_symbol) return;
			}
			ReshowFigure(current->x, current->y, x,y);
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
			
			
			ReshowFigure(current->x, current->y, x, y);	
			
			delete[] x;
			delete[] y;
		}
		void ReshowFigure(int* oldx, int* oldy, int* x, int* y){
			for (int ind=0; ind<Figure::size; ind++){
				setcursor(oldx[ind]+1, oldy[ind]+1);
				std::cout << arr[oldy[ind]][oldx[ind]] << arr[oldy[ind]][oldx[ind]+1];
			}
			for (int ind=0; ind<Figure::size; ind++){
				setcursor(x[ind]+1, y[ind]+1);
				std::cout << "[]";
				current->x[ind] = x[ind];
				current->y[ind] = y[ind];
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
				}
				if (burn){
					for (int col=0; col<w; col++){
						arr[row][col] = Board::void_symbol;
					}
				}
				for (int col=0; col<w; col++){
					if (arr[row][col] != Board::void_symbol){
						shift = false;
					}
				}
				if (shift && row>0){
					for (int col=0; col<w; col++){
						std::swap(arr[row][col], arr[row-1][col]);
					}
				}
			}
			Show();
		}
};
char Board::void_symbol = ' ';

