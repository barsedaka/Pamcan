#pragma once

#include "func.h"
#include "Creature.h"

class Fruit: public Creature
{
private:
	
	int point;	

public:
	Fruit(int x = 0,int y = 0,int _point=6):Creature(point+'0', x,y)
	{
		point = _point;
	}
	void moveFruit(int maxX, int maxY, char& direction);
	bool drawF(int x, int y, int game_Mode, int silentM);
	void setPoint(int p);
	int getPoint()const;
};

