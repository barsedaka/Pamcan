#pragma once
#include "func.h"

/* The department that bequeaths its properties to spirits, Pacman and fruit.*/

class Creature
{
protected:
	int x; 
	int y; 
	char look; 
	enum { min_x = 1, min_y = 1 }; // Screen limitation

public: 
	Creature(char _look, int _x = 1, int _y = 1) {
		x = _x; 
		y = _y;
		look = _look;
	}

	void setX(int x);
	void setY(int y);
	int getX()const;
	int getY()const;

	void draw(int x, int y);
	void checkdir(int maxX, int maxY);
};

