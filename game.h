#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <string>
#include <filesystem>

#include <windows.h> 

#include "func.h"
#include "board.h"
#include "Creature.h"
#include "NoviceGhost.h"
#include "BestGhost.h"
#include "GoodGhost.h"


//using std::filesystem::directory_iterator;

class Game
{
	bool winner, loser;
	int NumFilesInDirectory = 0;

public:
	Game()
	{
		winner = false;
		loser = false;
	}
	int gameMode();
	int menu();
	void startGame(int game_Mode, int silentM,int ans);
	std::string openFile(int& _x, int& _y, int& numBoard, std::vector<std::string> ArrFile, std::string& filesteps, std::string& fileresult);
	void calcSizeOfBoard(int& _x, int& _y, std::ifstream& MyFile);
	void printinst()const;
	void move(Pacman& pac, int ans,int _x,int _y, std::string filename, std::string filesteps, std::string fileresult, int game_Mode,int silentM);
	void printByChar(char ch, int x, int y);
	void printLivesAndPoints(int lives, int points,int x_legend, int y_legend);
	void Delete(int x, int y);
	void printandsetStartPos(Pacman& pac,  int firstpos[], Board& board, int size,Ghost* ARR[],int silentM);
	void getAllCoor(Pacman& pac, Ghost* ARR[],  int numGhosts, int& x_pac, int& y_pac, int exGpoints[], Fruit& pri, int& exFX, int& exFY);
	void setGhostCoor(Ghost& ghost, int x_ghost, int y_ghost);
	void setFruitCoor(Fruit& pri, int xF, int yF);
	void setPac(char& dir, char& Xdir, Board& board, Pacman& pac, bool legendInFirstRow, char& direction);
	void setAll(Pacman& pac, Ghost& g1, Ghost& g2);
	void initFirstPos(int firstPos[], int size, Pacman& pac,Ghost* ARR[]);
	void checkdir(int max_x, int max_y, Board& board, Pacman& pac, bool legendInFirstRow, bool& setMaxY,int addy, int silentM);
};

#endif