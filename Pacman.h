#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Creature.h"
#include <windows.h>
#include "func.h"
//#include "board.h"


class Pacman:public Creature
{	
	int _points;
	int _lives;
public:	
	Pacman(int x=1,int y=1) : Creature('G',x,y) {

		_points = -1;
		_lives = 3;

	}	
	int getPoints()const;
	void setPoints();
	void setPoints(int x,int add=0);
	void setLives(int x);
	int getLives()const;
	void setLives();
	//void checkdir(int max_x,int max_y,char ch);
};

#endif