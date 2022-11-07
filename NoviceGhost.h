#pragma once
#include "ghost.h"

class NoviceGhost: public Ghost
{
public:
	NoviceGhost() : Ghost('C')
	{

	}
	void moveGhost(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80], char& direction)override;
};

