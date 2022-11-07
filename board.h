#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "func.h"
#include <string>
#include <fstream>
#include <vector>
#include "ghost.h"
#include "Pacman.h"
#include "Fruit.h"


class Board {

	
	char Mat[25][80] = { 0 };
	//bool visited[25][80] = { false };
	int width, length;
	int maxPOINTS;	
	
public:

	
	
	Board(int _x = 0, int _y = 0) : width(_x), length(_y) { maxPOINTS = 0; }
	int getWidth()const; 
	int getLength()const; 	
	char getchar(int x, int y)const;
	void setchar(const char ch, int x, int y);
	
	int getMAXPOINTS();
	void setMAXPOINTS(int num,int add);
	void printgame(int _x,int _y, int x_legend,int y_legend)const;
	bool checkIfFoodCoor(int x, int y);
	bool checkIfHit(int x, int y, bool flag,bool legendInFirstRow);
	bool checkIfCrushed(int x_p, int y_p, int x_g, int y_g);	
	void setBoard(Board& board, std::string filename, int& logSize, Pacman& pac, int& numGhosts, Fruit& pri, Ghost* ARR[], int& x_legend, int& y_legend, bool& legendInFirstRow, bool(&visited)[25][80], std::ofstream& Mystepsstd,std::ifstream& MystepsR, int game_mode);
	void setLegendInBoard(Board& board, int x_legend, int y_legend, bool& setMaxY,int& addy, bool(&visited)[25][80]);
	//void printLivesAndPoints(int lives, int points);
	void RandFruit(Fruit& pri, int x_p, int y_p);
};


#endif