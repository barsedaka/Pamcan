#include "ghost.h"

/*This function accepts as a parameter the current coordinate of the pacman and moves
  the ghosts according to its location (the winds chase the pacman)*/


void Ghost::moveS(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80], char& direction)
{
	int wheretogo;
	bool found = false;
	static int prev_x = 0;
	static int prev_y = 0;
	int prevX = x;
	int prevY = y;
	int counter = 0;
	bool moveTry[4] = { false };//up-0,right-1,down-2,left=3
	int m = 0;
	bool flag = false;
	wheretogo = rand() % 2 + 1;
	do {
		if (counter > 1)
		{
			wheretogo = 5;

			flag = false;

			for (; m < 4 && !flag; m++)
			{
				if (!moveTry[m])
				{
					if (m == 0)
					{
						prevY = y;
						direction = 'U';
						y = y - 1;
						flag = true;
					}
					if (m == 1)
					{
						prevX = x;
						direction = 'R';
						x = x + 1;
						flag = true;
					}
					if (m == 2)
					{
						prevY = y;
						direction = 'D';
						y = y + 1;
						flag = true;
					}
					if (m == 3)
					{
						prevX = x;
						direction = 'L';
						x = x - 1;
						flag = true;
					}
					moveTry[m] = true;
				}
			}
		}
		if (wheretogo == 1)
		{

			if ((x - _x) < 0)
			{
				prevX = x;
				direction = 'R';
				x = x + 1;
				moveTry[1] = true;
			}
			else
			{
				prevX = x;
				direction = 'L';
				x = x - 1;
				moveTry[3] = true;
			}
			wheretogo = 2;
		}
		else if (wheretogo == 2) {

			if (((y - _y) < 0))
			{
				prevY = y;
				direction = 'D';
				y = y + 1;
				moveTry[2] = true;
			}
			else
			{
				prevY = y;
				direction = 'U';
				y = y - 1;
				moveTry[0] = true;
			}
			wheretogo = 1;
		}
		if ((visited[y][x] != true))
		{
			prev_x = x;
			prev_y = y;

			found = true;

		}

		else {
			y = prevY;
			x = prevX;
		}
		counter++;
	} while (!found);
}