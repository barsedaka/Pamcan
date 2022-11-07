#include "board.h"

using std::string;

int Board::getWidth()const
{
	return width; 
}
int Board::getLength()const
{
	return length; 
}

/*This function receives a coordinate and returns the character found on the board in that coordinate*/
char Board::getchar(int x, int y)const
{
	return Mat[y][x];
}

void Board::setchar(const char ch, int x, int y)
{
	Mat[y][x] = ch;
}

/*This function prints the board of the game*/
void Board::printgame(int _x,int _y, int x_legend,int y_legend)const
{
	gotoxy(0, 0);	
	for (int k = 0; k < _y; k++)//Y
	{
		for (int i = 0; i < _x; i++)//X
		{
			char ch = getchar(i, k);
			if ((k >= y_legend && k <= y_legend + 2) && (i >= x_legend && i <= x_legend + 19))
				std::cout << " ";
			else
				std::cout << ch;
		}
		std::cout << std::endl;
	}
}
/*This function checks whether the resulting coordinate is food. If so it changes the matrix to contain a space
(the pacman ate the food so we will update the board accordingly) and returns true, otherwise returns false*/
bool Board::checkIfFoodCoor(int x, int y)
{
	if (Mat[y][x] == '.')
	{
		Mat[y][x] = ' ';
		return true;
	}
	return false;
}
/*This function checks whether the coordinate obtained as a parameter represents the inner walls
  (whether the creature is stuck in the wall)
  flag is true when pacman activate the function and false when the ghost activate the function*/
bool Board::checkIfHit(int x, int y, bool flag,bool legendInFirstRow)
{
	if (flag)
	{
		if (!legendInFirstRow)
		{
			if (Mat[y][x] == 'x' && (y != 0 && x != 0 && x != width - 1 && y != length - 1))
				return true;
		}
		else {
			if (Mat[y][x] == 'x')
				return true;
		}
	}
	else
		if (Mat[y][x] == 'x')
			return true;
	
	return false;
}

/*This function checks if one of the ghosts/fruit collided with Pacman*/
bool  Board::checkIfCrushed(int x_p, int y_p, int x_g, int y_g)
{
	if (x_p == x_g && y_p == y_g)
		return true;
	return false;
}

void Board::setBoard(Board& board, std::string filename, int& logSize, Pacman& pac, int& numGhosts, Fruit& pri, Ghost* ARR[], int& x_legend, int& y_legend, bool& legendInFirstRow, bool(&visited)[25][80], std::ofstream& Mysteps, std::ifstream& MystepsR,int game_mode )
{
	std::ifstream MyFile;
	char ch;
	int _x=0,_y=0; 
	MyFile.open(filename);
	string line;
	
	bool setByLegend = false; 
	while (!MyFile.eof())
	{
		ch = MyFile.get(); 
		
		if (ch == '\n')
		{
			_y++; 
			_x=-1; 
		}

		else if (ch == ' ')//bread
		{
			Mat[_y][_x] = '.';
			maxPOINTS++;
		}
		else if (ch == '@')//Pacman
		{
			if (game_mode != 3) {
				pac.setX(_x);
				pac.setY(_y);
			}
			Mat[_y][_x] = 'G';
		}
		else if (ch == '$')//Ghost
		{
			if (game_mode != 3) {
				ARR[numGhosts]->setX(_x);
				ARR[numGhosts]->setY(_y);
			}
			
			Mat[_y][_x] = '.';
			numGhosts++;
		}
		else if (ch == '#')
		{
			Mat[_y][_x] = 'x';
			visited[_y][_x] = true;
		}
		else if (ch == '%')
		{
			Mat[_y][_x] = ' ';
		}
		
		else if (ch == '&')
		{
			x_legend = _x;
			y_legend = _y;
			if (_y == 0)
			{
				legendInFirstRow = true;
				if (width-1 < _x + 19)//If the & is in the first row and also the length of the first row is smaller than the position of the & plus 19
					width =_x+ 19; 				
			}

		}

		_x++;
	}
	if(game_mode!=3)
		RandFruit(pri, pac.getX(), pac.getY());

	if (game_mode == 2) {
		Mysteps << numGhosts << " ";
		for (int i = 0; i < numGhosts; i++)
			Mysteps << ARR[i]->getX() << " " << ARR[i]->getY() << " ";
		Mysteps << pac.getX() << " " << pac.getY() << " "<<pri.getPoint()<<' '<< pri.getX() << " " << pri.getY() << std::endl;
	}
	/*in case the user chose load game, we will read the coordinations of the creatures from the steps file */
	int xTemp, yTemp; 
	if (game_mode == 3) {
		MystepsR >> numGhosts;
		for (int i = 0; i < numGhosts; i++) {
			MystepsR >> xTemp >> yTemp; 
			ARR[i]->setX(xTemp);
			ARR[i]->setY(yTemp);
		}
		MystepsR >> xTemp >> yTemp;
		pac.setX(xTemp); 
		pac.setY(yTemp); 
		MystepsR >>xTemp>> xTemp >> yTemp;
		pri.setX(xTemp); 
		pri.setY(yTemp);
	}


}

/*
* If the & is in the last line, or one in front of me, or two in front of it, then it is necessary to add lines to the board for the size of the reading & [20X3]
And also initialize all the rows we added in 'x'
*/
void Board::setLegendInBoard(Board& board,int x_legend, int y_legend,bool& setMaxY,int& addy, bool(&visited)[25][80])
{
	bool add = false;
	int x = x_legend; 
	int y = y_legend; 
	if (y == length)
	{
		length = length + 3;
		addy = 3;
		add = true;
		setMaxY = true; 
	}
		
	if (y == length - 1)
	{
		length = length + 2;
		addy = 2;
		add = true;
		setMaxY = true;
	}
	if (y == length - 2)
	{
		length = length+1;
		addy = 1;
		add = true;
		setMaxY = true;
	}
		
	for (int i = y; i < y+3; i++)
	{
		for (int j = x; j < x+20; j++)
		{
			Mat[i][j] = 'x';
			visited[i][j] = true;
		}
	}
	if (add)
	{
		for (int i = y; i < y + 3; i++)
		{
			for(int m=x+20;m<width;m++)
				Mat[i][m] = ' ';
		}

	}
}

/* This function randomly selects a valid location for the fruit (a valid location-place where there is no wall + not the location of the pacman)*/
void Board::RandFruit(Fruit& pri, int x_p, int y_p)
{
	int newx;
	int newy;

	do {
		newx = rand() % (width-1) + 1;
		newy = rand() % (length-1) + 1;

	} while (Mat[newy][newx] == 'x' || (newy == y_p && newx == x_p));
	pri.setX(newx);
	pri.setY(newy);
}

int Board:: getMAXPOINTS()
{
	return maxPOINTS;
}
void Board::setMAXPOINTS(int num,int add)
{
	maxPOINTS = num + add;
}