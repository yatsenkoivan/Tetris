#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
char s = 219; //symbol 'white square', will be used to show figures.
const int board_x = 10;
const int board_y = 20;


struct element{
	int color = 0;
	/*9  - blue
	  12 - red
	  14 - yellow
	  10 - green
	  13 - pink
	  11 - light blue
	*/
	int type = 0;
	/*
		1:
	  		*@**
		2:
			*
			*@*
		3:
			  *
			*@*
		4:
			**
			@*
		5:
			 **
			*@
		6:
			**
			 @*
		7:
			 *
			*@*
			
	*/
	
	int start_x = 0; //@'s x
	int start_y = 0; //@'s y
	
};

//board of figures (info in structs)
element** board = new element*[board_y];

//set_board
void set_board(){
	for (int i=0; i<board_y; i++){
		board[i] = new element[board_x];
	}
}


//set color of text (figures)
void set_color(int color_id){
	SetConsoleTextAttribute(h, color_id);
}

void create_object(int color, int type){
	
	/*
	
	@@@@
	
	*/
	if (type == 1){
		for (int i=3; i<7; i++){
			board[0][i].color = color;
		}
	}
	
	
	/*
	
	@
	@@@
	
	*/
	if (type == 2){
		board[0][3].color = color;
		for (int i=3; i<6; i++){
			board[1][i].color = color;
		}
	}
	
	/*
	
	  @
	@@@
	
	*/
	if (type == 3){
		board[0][5].color = color;
		for (int i=3; i<6; i++){
			board[1][i].color = color;
		}
	}
	
	/*
	
	@@
	@@
	
	*/
	if (type == 4){
		
		for (int i=4; i<6; i++){
			board[0][i].color = color;
			board[1][i].color = color;
		}
	}
	
	/*
	
	 @@
	@@
	
	*/
	if (type == 5){
		
		for (int i=3; i<5; i++){
			board[0][i+1].color = color;
			board[1][i].color = color;
		}
	}
	
	
	/*
	
	@@
	 @@
	
	*/
	if (type == 6){
		
		for (int i=3; i<5; i++){
			board[1][i+1].color = color;
			board[0][i].color = color;
		}
	}
	
	/*
	
	 @
	@@@
	
	*/
	if (type == 7){
		board[0][4].color = color;
		for (int i=3; i<6; i++){
			board[1][i].color = color;
		}
	}
	
	
}

void print_board(){
	for (int i=0; i<board_x+2; i++){
		cout << "-";
	}
	cout << endl;
	for (int i=0; i<board_y; i++){
		cout << "|";
		for (int j=0; j<board_x; j++){
			if (board[i][j].color != 0){
				set_color(board[i][j].color);
				cout << s;
				set_color(7); //set color to white;
				continue;
			}
			cout << " ";
			
		}
		cout << "|" << endl;
	}
	
	for (int i=0; i<board_x+2; i++){
		cout << "-";
	}
	
	cout << endl;
	
}

int main(){
	
	srand(time(NULL));
	
	set_board();
	
	cout << "/------TETRIS------/\n";
	cout << "a, d - to move\nq, e - to rotate\ns - to fast put\n\n";
	cout << "Press any key to continue . . .";
	_getch();
	system("cls");
	
	bool game = true;
	bool is_figure_controlled = false; //if we currently controlling figure
	
	int color_temp = 0;
	int type_temp = 0;
	
	while (game){
		if (!is_figure_controlled){
			color_temp = rand()%6+9;
			type_temp = rand()%7+1;
			cout << color_temp << " " << type_temp << endl;
			create_object(color_temp, type_temp);
			is_figure_controlled = true;
			
		}
		
		print_board();
		
		char move{};
		if (kbhit()){ //when something is pressed
			
			
		}
		move = _getch();
		system("cls");
	}
	
}
