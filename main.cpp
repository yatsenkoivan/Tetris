#include "tetris.h"
#include <conio.h>

int main(){
	Board b;
	Sleep(1000);
	b.Show();
	b.NewFigure();
	char move;
	
	double delay = 160;
	
	clock_t start = clock();
	clock_t end = clock();
	double diff;
	
	while (true){
		if (kbhit()){
			move = _getch();
			b.Press(move);
		}
		end = clock();
		diff = difftime(end,start);
		if (diff >= delay){
			b.Fall();
			start = clock();
		}
	}
}
