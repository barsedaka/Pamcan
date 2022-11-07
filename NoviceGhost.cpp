#include "NoviceGhost.h"


void NoviceGhost::moveGhost(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80], char& direction)
{
	static int ind = 0;
	static int dir;

	if (ind < 20 * numGhosts)
	{
		if (ind == 0)
		{
			dir = rand() % 4 + 1;
		}

		ind++;
	}
	else
		ind = 0;

	if (dir == 1)
	{

		x = x + 1;
		direction = 'R';
	}

	else if (dir == 2)
	{
		x = x - 1;
		direction = 'L';
	}

	else if (dir == 3)
	{
		direction = 'D';
		y = y + 1;
	}

	else
	{
		direction = 'U';
		y = y - 1;
	}

	checkdir(maxX, maxY);
}

