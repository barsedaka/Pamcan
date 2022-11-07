#include "Fruit.h"


void Fruit::setPoint(int p)
{
	point = p;
}

int Fruit::getPoint()const
{
	return point;
}
/*
At every 35 steps the fruit randomly selects a new number
*/
bool Fruit:: drawF(int x, int y,int game_Mode,int silentM)
{
	static int count = 0;
	

	if (count < 35 )
	{
		if (game_Mode != 3)
		{
			if (count == 0)
			{
				point = 5 + (rand() % (9 - 5 + 1));
			}
		}
		count++;
		gotoxy(x, y);
		if (silentM == 2)
			std::cout << point;
		
			
	}
	else {
		count = 0;
		gotoxy(x, y);
		if (silentM == 2)
			std::cout << point;
		return true;
	}
	return false;
}

void Fruit::moveFruit(int maxX,int maxY,char& direction)
{
	
	int dir;	
	dir = rand() % 4 + 1;
	
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