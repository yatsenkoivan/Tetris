#pragma once
#include <iostream>


class Board{
	private:
		int w;
		int h;
	public:
		Board(int w, int h) : w{w*2}, h{h} {}
		Board() : Board(10, 20) {}
		void Show(){
			system("cls");
			std::cout << '+';
			for (int col=0; col<w; col++) std::cout << '-';
			std::cout << '+' << std::endl;
			for (int row=0; row<h; row++){
				std::cout << '|';
				for (int col=0; col<w; col++) std::cout << ' ';
				std::cout << '|' << std::endl;
			}
			std::cout << '+';
			for (int col=0; col<w; col++) std::cout << '-';
			std::cout << '+' << std::endl;
		}
};
