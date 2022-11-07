#include "GoodGhost.h"



void GoodGhost::moveGhost(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80], char& direction)
{
	static int index = 0;
	static int counter = 0;
	static int dir;
	if (index < 20 * numGhosts) {
		
		moveS(_x, _y, ans, numGhosts, maxX, maxY, visited,direction);

		index++;
	}
	else {
		if (counter < 5 * numGhosts)
		{
			if (counter == 0)
			{
				dir = rand() % 4 + 1;
			}

			counter++;
		}
		else {
			counter = 0;
			index = 0;

		}
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
}