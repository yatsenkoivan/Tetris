#include <conio.h>
#include <time.h>
#include "tetris.h"

int main(){
	
	float delay = 0.4;
	
	srand(time(0));
	
	Figure f;
	
	f.set();
	
	welcome();
	start();
	system("cls");
	f.set();
	
	time_t start = time(0);
	time_t end = time(0);
	float dif;
	
	char dir;
	
	show_board(f);
	while (true){
		
		if (kbhit()){
			dir = _getch();
			f.move(dir);
			if (f.color == 0) f.set();
			system("cls");
			show_board(f);
		}
		
		end = time(0);
		dif = difftime(end, start);
		
		if (dif >= delay){
			start = time(0);
			f.move('s');
			if (f.color == 0) f.set();
			system("cls");
			show_board(f);
		}
	}
}



