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
		int lvl;
		int lines;
		int score;
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
			lvl=1;
			lines=0;
			score=0;
		}
		Board() : Board(10, 20) {}
		~Board(){
			for (int row=0; row<h; row++){
				delete[] arr[row];
			}
			delete[] arr;
		}
		void Show(){
			setcursor(0,0);
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
			ShowLVL();
			ShowLVLValue();
			ShowLinesCount();
			ShowLinesCountValue();
			ShowScore();
			ShowScoreValue();
		}
		void ShowNext(){
			ShowTable(Figure::size*2+4, 4,0);
		}
		void ShowLVL(){
			ShowTable(10,3,5);
		}
		void ShowLVLValue(){
			setcursor(w+2+2, 5+2);
			std::cout << "      ";
			setcursor(w+2+2, 5+2);
			std::cout << "LVL: " << lvl;
		}
		void ShowLinesCount(){
			ShowTable(14,3,9);
		}
		void ShowLinesCountValue(){
			setcursor(w+2+1, 9+2);
			std::cout << "            ";
			setcursor(w+2+1, 9+2);
			std::cout << "LINES: " << lines;
		}
		void ShowScore(){
			ShowTable(16, 3, 13);
		}
		void ShowScoreValue(){
			setcursor(w+2+1, 13+2);
			std::cout << "                ";
			setcursor(w+2+1, 13+2);
			std::cout << "SCORE: " << score;
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
		void ShowTable(int width, int height, int lvl){
			setcursor(w+2, lvl);
			for (int col=0; col<width+1; col++) std::cout << '-';
			std::cout << '+';
			for (int row=0; row<height; row++){
				setcursor(w+2+width+1, lvl+row+1);
				std::cout << '|';
			}
			setcursor(w+2, lvl+height+1);
			for (int col=0; col<width+1; col++) std::cout << '-';
			std::cout << '+';
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
					if (NewFigure() == false) GameOver();
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
			int burnt=0;
			for (int row=h-1; row>=0; row--){
				burn = true;
				for (int col=0; col<w; col++){
					if (arr[row][col] == Board::void_symbol){
						burn = false;
					}
				}
				if (burn){
					burnt++;
					for (int col=0; col<w; col++){
						arr[row][col] = Board::void_symbol;
					}
				}
			}
			int ind=h-1;
			for (int row=h-1; row>=0; row--){
				for (int col=0; col<w; col++){
					if (arr[row][col] != Board::void_symbol){
						std::swap(arr[row], arr[ind]);
						ind--;
						break;
					}
				}
			}
			lines+=burnt;
			Show();
			ShowLVLValue();
			ShowLinesCountValue();
			ShowScoreValue();
		}
		void GameOver(){
			setcursor(0, h+2);
			std::cout << "GAME OVER\n";
			exit(0);
		}
};
char Board::void_symbol = ' ';

