#include "Pacman.h"


int Pacman::getLives()const
{
	return _lives;
}

int Pacman::getPoints()const
{
	return _points;
}



/*This function increases the number of points of the pacman
 (this happens if he reaches the coordinate where he had food)*/
void Pacman::setPoints()
{
	_points = _points + 1;
}

void Pacman::setPoints(int x,int add)
{
	_points = x+add;
}

/*This function lowers Pacman's life (this happens when one of the ghosts hits him)*/
void Pacman::setLives()
{
	_lives = _lives - 1;
}

void Pacman::setLives(int x)
{
	_lives = x;
}

