#ifndef _GHOST_H_
#define _GHOST_H_


#include "func.h"
#include "Creature.h"


/*The class that bequeaths its qualities to all kinds of Ghosts- a BEST, GOOD, and NOVICE
*/
class Ghost:public Creature
{
	char level;

public:
	
	Ghost(char _level, int x = 0, int y = 0) : Creature('~', x, y) {
		level = _level;
	}
	
	virtual void moveGhost(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80],char& direction)=0;
	void moveS(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80],char& direction);

};

#endif