#include "tetris.h"
#include <conio.h>

int main(){
	Board b;
	b.NewFigure();
	b.Show();
	b.ShowFigure();
	
	char move;
	while (true){
		move = _getch();
		b.Press(move);
	}
}
