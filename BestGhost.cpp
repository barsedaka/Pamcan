#include "BestGhost.h"
 /*First the whole function checks by the distance of the shortest X \ Y,
 if it encounters both 'x' then it updates in a Boolean array indicating where "we have already tried to go" (up, down, right, left)
 and then it goes to a place it is not yet Tried to go to it when she finds a normal Cordnita that does not have an 'x'
 and then the loop ends.
Then everything comes back again.*/
void BestGhost::moveGhost(int _x, int _y, char ans, int numGhosts, int maxX, int maxY, bool(&visited)[25][80], char& direction)
{
	moveS(_x, _y, ans, numGhosts, maxX, maxY, visited,direction);

}
