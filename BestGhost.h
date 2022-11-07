#pragma once

#include "ghost.h"

class BestGhost:public Ghost
{
public:
	BestGhost() : Ghost('A')
	{

	}
	 void moveGhost(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80], char& direction)override;
	 
};

