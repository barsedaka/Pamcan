#include "Creature.h"


void Creature::setX(int _x)
{
	x = _x; 
}
void  Creature::setY(int _y)
{
	y = _y; 
}
int  Creature::getX()const
{
	return x; 
}
int  Creature::getY()const
{
	return y;
}

void Creature::draw(int x, int y)//The function prints the shape of the creature
{
	gotoxy(x, y);
	std::cout << look;
}
void Creature::checkdir(int maxX, int maxY)
{
	int x = getX();
	int y = getY();

	if (x > maxX)
	{
		setX(maxX - 1);
	}
	else if (x < min_x)
	{
		setX(min_x + 1);
	}
	if (y > maxY)
	{
		setY(maxY - 1);
	}
	else if (y < min_y)
	{
		setY(min_y);
	}
}
