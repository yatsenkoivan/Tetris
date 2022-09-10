#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <time.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
char s = 219; //symbol 'white square', will be used to show figures.
const int board_x = 20;
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

struct controll{
	vector<int> x{};
	vector<int> y{};
	int color = 0;
	/*9  - blue
	  12 - red
	  14 - yellow
	  10 - green
	  13 - pink
	  11 - light blue
	*/
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

void create_object(int color, int type, controll& figure){
	figure.color = color;
	/*
	
	@@@@
	
	*/
	if (type == 1){
		for (int i=3; i<7; i++){
			board[0][i].color = color;
			figure.x.push_back(i);
			figure.y.push_back(0);
		}
	}
	
	
	/*
	
	@
	@@@
	
	*/
	if (type == 2){
		board[0][3].color = color;
		figure.x.push_back(3);
		figure.y.push_back(0);
		for (int i=3; i<6; i++){
			board[1][i].color = color;
			figure.x.push_back(i);
			figure.y.push_back(1);
		}
	}
	
	/*
	
	  @
	@@@
	
	*/
	if (type == 3){
		board[0][5].color = color;
		figure.x.push_back(5);
		figure.y.push_back(0);
		for (int i=3; i<6; i++){
			board[1][i].color = color;
			figure.x.push_back(i);
			figure.y.push_back(1);
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
			figure.x.push_back(i);
			figure.y.push_back(0);
			figure.x.push_back(i);
			figure.y.push_back(1);
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
			figure.x.push_back(i+1);
			figure.y.push_back(0);
			figure.x.push_back(i);
			figure.y.push_back(1);
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
			figure.x.push_back(i+1);
			figure.y.push_back(1);
			figure.x.push_back(i);
			figure.y.push_back(0);
		}
	}
	
	/*
	
	 @
	@@@
	
	*/
	if (type == 7){
		board[0][4].color = color;
		figure.x.push_back(4);
		figure.y.push_back(0);
		for (int i=3; i<6; i++){
			board[1][i].color = color;
			figure.x.push_back(i);
			figure.y.push_back(1);
		}
	}
	
	
}

bool _find(vector<int> arr, int elem){
	for (int i: arr){
		if (i == elem) return true;
	}
	return false;
}

bool figure_fall(controll &figure){
	element temp{};
	for (int i=0; i<4; i++){
		if (figure.y[i] >= board_y-1) return false;
		if (!_find(figure.y, figure.y[i]+1)){
			if (board[figure.y[i]+1][figure.x[i]].color != 0) return false;
		}
		
		
	}
	
	for (int i=3; i>=0; i--){
		//cout << figure.y[i] << " " << figure.x[i] << endl;
		//_getch();
		board[figure.y[i]][figure.x[i]].color = 0;
		figure.y[i]++;
	}
	for (int i=3; i>=0; i--){
		board[figure.y[i]][figure.x[i]].color = figure.color;
	}
	return true;
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


bool move_func(char move, controll &figure){
	
	if (move == 's'){
		while (true){
			if (!figure_fall(figure)) break;
		}
		return true;
	}
	
	int step = 0;
	if (move == 'd') step = -1; //end-1 of x
	if (move == 'a') step = -20; //start+1 of x
	
	for (int i=0; i<4; i++){
		if (figure.x[i] == board_x+step) return false;
	}
	
	if (move == 'd') step = 1;
	if (move == 'a') step = -1;
	
	for (int i=0; i<4; i++){
		board[figure.y[i]][figure.x[i]].color = 0;
		figure.x[i] += step;
	}
	for (int i=0; i<4; i++){
		board[figure.y[i]][figure.x[i]].color = figure.color;
	}
	return true;
	
}


int main(){
	
	srand(time(NULL));
	
	set_board();
	
	cout << "/------TETRIS------/\n";
	cout << "a, d - to move\nw - to rotate\ns - to fast put\n\n";
	cout << "Press any key to continue . . .";
	_getch();
	system("cls");
	
	bool game = true;
	bool is_figure_controlled = false; //if we currently controlling figure
	
	int color_temp = 0;
	int type_temp = 0;
	controll controlled_figure{};
	char move{};
	
	while (game){
		if (!is_figure_controlled){
			color_temp = rand()%6+9;
			type_temp = rand()%7+1;
			create_object(color_temp, type_temp, controlled_figure);
			
			
			is_figure_controlled = true;
			
		}
		
		print_board();
		
		if (kbhit()){
			move = _getch();
			move_func(move, controlled_figure);
		}
		Sleep(500);
		if (!figure_fall(controlled_figure)){
			is_figure_controlled = false;
			controlled_figure.color = 0;
			controlled_figure.x.clear();
			controlled_figure.y.clear();
		}
		system("cls");
	}
	
}
