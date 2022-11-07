#pragma once
#include "ghost.h"

class GoodGhost:public Ghost
{

public: 
	GoodGhost() : Ghost('B')
	{

	}
	void moveGhost(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80], char& direction)override;
};

