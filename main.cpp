#include "game.h"
#include <conio.h>
#include <string.h>


int main(int argc,char**argv)
{
	Game game;
	int GMode=1;
	int silentM=2;
	GMode =3;
	int ans = 1;
	
	if (argc < 2) //There is no parameters, run "simple" game
		GMode = 1;
	else if (strcmp(argv[1], "save") == 0)
		GMode = 2; 
	else if((strcmp(argv[1], "load") == 0)&&argc==2)
		GMode = 3;
	else if ((strcmp(argv[1], "load") == 0)&& (strcmp(argv[2],"silent")==0))
	{
		GMode = 3; 
		silentM = 1;
	}
	
	game.startGame(GMode,silentM,ans);

}
