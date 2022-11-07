#include "game.h"
#include <string.h>
#define CRT_SECURE_NO_WARNINGS
#define __STDC_WANT_LIB_EXT1__ 1

void Game::printinst()const
{
	int ans;
	clrscr();

	do {
		std::cout << "keys: " << std::endl;
		std::cout << std::endl;
		std::cout << "LEFT " << "         " << "a or A" << std::endl;
		std::cout << "RIGHT" << "         " << "d or D" << std::endl;
		std::cout << "UP   " << "         " << "w or W" << std::endl;
		std::cout << "DOWN " << "         " << "x or X" << std::endl;
		std::cout << "STAY " << "         " << "s or S" << std::endl;

		std::cout << "Press 1 to see the menu again" << std::endl;
		std::cin >> ans;
		clrscr();
	} while (ans != 1);

}

void Game::setAll(Pacman& pac, Ghost& g1, Ghost& g2) {
	pac.setX(1);
	pac.setY(1);
	pac.setPoints(-1);
	pac.setLives(3);
	g1.setX(15);
	g1.setY(15);
	g2.setX(10);
	g2.setY(10);
}
/*
This function checks if the file name starts with- "pacman_" and ends with ".screen"
*/
bool checkFileName(std::string& filename)
{
	char pacman[8];
	char screen[8];

	if (filename.length() < 14)
		return false;
	filename.copy(pacman, 7, 0);
	filename.copy(screen, 7, filename.length() - 7);
	pacman[7] = '\0';
	screen[7] = '\0';
	return(strcmp(pacman, "pacman_") == 0 && strcmp(screen, ".screen") == 0);

}
/* The function asks the user if he wants to select a file or the program will select for him.
Then, at his choice she opens the requested file (if the program chooses for him, then in a lexicographical way).*/
std::string Game::openFile(int &_x,int &_y,int &numBoard,std::vector<std::string> ArrFile, std::string& filesteps, std::string& fileresult)
{
	std::ifstream MyFile;
	std::string filename;
	std::string steps=".steps";
	std::string result = ".result";
	
	static int ans=1;
	if (numBoard == 1)
	{
		std::cout << "Hey, Do you want to choose a file?" << std::endl;
		do {
			std::cout << "Press 1-YES 2-NO" << std::endl;
			std::cin >> ans;
			clrscr();
		} while (ans != 1 && ans != 2);
	}
	
	
	if (NumFilesInDirectory == 0)
	{
		std::cout << "There's No File In The Directory..... Soorryyyy!!!";
		exit(1);
	}
		
	
	if (ans == 1)
	{
		bool flag = false; 
		do {
			std::cout << "Enter the filename" << std::endl;
			std::cin >> filename;
			flag = checkFileName(filename);

		} while (!flag);
		
		MyFile.open(filename);
		calcSizeOfBoard(_x, _y, MyFile);
	}
	
	else {
		
		if (numBoard == 1)
		{
			filename = ArrFile[numBoard - 1];
			MyFile.open(filename);
			calcSizeOfBoard(_x, _y, MyFile);

		}

		else if (numBoard == 2)
		{
			if (!(NumFilesInDirectory > 1))
				exit(1);
			filename = ArrFile[numBoard - 1];
			MyFile.open(filename);;
			calcSizeOfBoard(_x, _y, MyFile);
		}

		else
		{
			if (!(NumFilesInDirectory > 2))
				exit(1);
			filename = ArrFile[numBoard - 1];
			MyFile.open(filename);
			calcSizeOfBoard(_x, _y, MyFile);

		}
	}
	MyFile.close();
	int m = filename.length();
	int newm = m - 7;
	
	filesteps.resize(m);
	fileresult.resize(m);
	int w = 0;
	for (int i = 0; i < m; i++)
	{
		if (i < newm)
		{
			filesteps[i] = filename[i];
			fileresult[i] = filename[i];
		}
			
		else
		{
			filesteps[i] = steps[w];
			fileresult[i] = result[w++];
		}
			
	}
	
	return filename;
}

/*This function get board and calculate his length and width*/
void Game::calcSizeOfBoard(int& _x, int& _y, std::ifstream& MyFile)
{
	std::string line;
	if (!MyFile) {
		std::cout << "Error, file couldn't be opened" << std::endl;
		exit(1);
	}
	

	while (std::getline(MyFile, line))
	{
		
		if (_x == 0)
			_x = line.length();
		_y++;
	}
	
	
}


/* The function prints the menu for the user and operates according to his choice */
void Game::startGame(int game_Mode,int silentM ,int ans)
{
	Pacman pac;
	
	//int ans = 1;
	int ans2=0;
	int _x = 0, _y = 0;
	bool runGame = false,RunFile=true;
	std::string filename;
	int Numgame = 1;
	std::string path = std::filesystem::current_path().string();
	std::vector<std::string> ArrFile;

	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		if (std::filesystem::path(file).extension() == ".screen")
		{
			ArrFile.push_back(file.path().string());

			NumFilesInDirectory++;
		}

	}
	std::string filesteps;
	std::string fileresult;
	int flag = 0;
	while (!runGame)
	{
		if (flag != 0)
		{
			ans = menu();			
		}
		
		if (flag == 0) {
			if (game_Mode == 3)
				ans = 1;
			else
			{
				ans = menu();
			}
		}
		
		switch (ans)
		{
		case 1:
			if (flag != 0)
				game_Mode = gameMode();
			if (game_Mode == 3&&flag!=0) {
				do {
					std::cout << "Do you want Silent Mode?" << std::endl; std::cout << "1)Yes " << std::endl; std::cout << "2)No" << std::endl;
					std::cin >> silentM;

				} while (silentM != 1 && silentM != 2);
				
			}
			flag = 1;
			runGame = true;
			RunFile = true;
			
			clrscr();
			while (RunFile)
			{

				std::cout << "for color press 1 , else press 2" << std::endl;;
				std::cin >> ans2;
				clrscr();
				_x = _y = 0;
				filename = openFile(_x, _y,Numgame,ArrFile, filesteps, fileresult);

				
				move(pac, ans2, _x, _y, filename,filesteps, fileresult, game_Mode,silentM);
				
				clrscr();
				if (pac.getLives() == 0) {
					if(silentM==2)
						std::cout << "LOOSERRRRRRR";		
						
					Sleep(2000);
					clrscr();
					runGame = false;
					pac.setLives(3);
					pac.setPoints(0,0);
					clrscr();
					
					RunFile = false;
										
				}

				else
				{
					std::cout << "wiinnerrrrr";
					Sleep(2000);
					clrscr();
					Numgame++;
					if (Numgame == 4)
						RunFile = false;
				}

			}
			
				
			break;

		case 8:

			printinst();
			ans = menu();
			break;

		case 9:
			clrscr();
			std::cout << "Good Bye!!!";
			Sleep(2000);
			runGame = true;
		}
	}

}

int Game::gameMode()
{
	int ans; 
	do
	{
		clrscr();
		std::cout << "Hey !!!!" << std::endl << "Welcome to Pacman!!!" << std::endl << "please choose one of the option:" << std::endl << "(1) Simple game" << std::endl << "(2) Save game" << std::endl << "(3) Load game" << std::endl;

		std::cin >> ans;

	} while (ans != 1 && ans != 2 && ans != 3);

	return ans;
}
int Game::menu()
{
	int ans;
	do
	{
		clrscr();
		std::cout << "Hey !!!!" << std::endl << "Welcome to Pacman!!!" << std::endl << "please choose one of the option:" << std::endl << "(1) Start a new game" << std::endl << "(8) Present instructions and keys" << std::endl << "(9) EXIT" << std::endl;

		std::cin >> ans;

	} while (ans != 1 && ans != 8 && ans != 9);

	return ans;
}

void Game::move(Pacman& pac, int ans, int _x, int _y, std::string filename, std::string filesteps, std::string fileresult, int game_Mode,int silentM)
{
	static int countertimegame = 0;
	std::ofstream Mysteps;
	std::ofstream Myresult;
	std::ifstream MystepsR;
	std::ifstream MyresultR;
	int counterdead = 0;
	if (game_Mode == 2)
	{
		Mysteps.open(filesteps);
		Myresult.open(fileresult);
	}
	if (game_Mode == 3)
	{
		MystepsR.open(filesteps);
		MyresultR.open(fileresult);
	}
	
	bool visited[25][80] = { false };
	
	char answer;
	if (game_Mode != 3) {
		do
		{
			clrscr();
			std::cout << "Please choose Level : " << std::endl << "A) Best" << std::endl << "B) Good" << std::endl << "C) Novice" << std::endl;

			std::cin >> answer;

		} while (answer != 'A' && answer != 'B' && answer != 'C');
	}
	else
		answer = 'A';
	clrscr();
	Ghost* ARR[4];//According to the user's choice of what level of game he wants, we will create an array of pointers for ghosts according to this level.
	for (int i = 0; i < 4; i++)
	{
		if (answer == 'A')
			ARR[i] = new BestGhost();
		if (answer == 'B')
			ARR[i] = new GoodGhost();
		if (answer == 'C')
			ARR[i] = new NoviceGhost();
	}

	int numGhosts = 0;
	int log_ghostArr = 0;
	int index = 0, i = 0;
	int x_legend, y_legend;

	if (ans == 1)
		system("Color 0C");
	Fruit pri;
	bool legendInFirstRow = false;
	bool setMaxY = false;
	int addy = 0;
	Board board(_x, _y);
	
	
	board.setBoard(board, filename,  log_ghostArr, pac,numGhosts,pri,ARR, x_legend, y_legend, legendInFirstRow,visited,Mysteps,MystepsR,game_Mode);
	
	board.setLegendInBoard(board, x_legend, y_legend,setMaxY,addy, visited);
	if(silentM==2)
		board.printgame(board.getWidth(),board.getLength(),x_legend,y_legend); //This function prints the board
	_x = board.getWidth();
	_y = board.getLength();
	int x_pac, y_pac;
	char dir = ' ', Xdir = ' ';
	bool con = true, start = false;
	bool run = true; //Represents whether Pacman has more life left in the game
	hideCursor();
	int* exGpoints = new int[numGhosts*2];
	int* firstPos = new int[numGhosts * 2 + 2];
	int exFX, exFY;
	initFirstPos(firstPos, numGhosts * 2 + 2, pac,ARR);
	bool changecoorFruit = false;
	char direction;

	while ((!_kbhit() || con) && run)
	{
		getAllCoor(pac,ARR, numGhosts, x_pac, y_pac, exGpoints,pri,exFX,exFY);
	

		if (start && index % 2 == 0) //START indicates whether the Pacman has started moving,
									 //and (index % 2 == 0) takes care that every two steps of the pacman , the ghosts will advance one step
		{
			/*Before we promote the ghosts, we will check in the characters array which character was there
			  before (dot or space) so that we can print it back on the screen and promote the ghosts.*/
			for (int m = 0; m < numGhosts*2; m+=2)
			{
				if (silentM == 2)
					printByChar(board.getchar(exGpoints[m], exGpoints[m+1]), exGpoints[m], exGpoints[m + 1]);
				
			}
			char ch;			
			for (int w = 0; w < numGhosts; w++)
			{
				if(game_Mode!=3)
					ARR[w]->moveGhost(x_pac, y_pac, answer, numGhosts, board.getWidth(), board.getLength(), visited,direction);
				if(game_Mode==2)
					Mysteps <<"G "<< direction <<' ';
				if (game_Mode == 3)
				{
					MystepsR >> ch;
					MystepsR >> ch;
					
					if (ch == 'U')
						ARR[w]->setY(ARR[w]->getY() - 1);
					else if(ch=='D')
						ARR[w]->setY(ARR[w]->getY() + 1);
					else if(ch=='R')
						ARR[w]->setX(ARR[w]->getX() + 1);
					else
						ARR[w]->setX(ARR[w]->getX() - 1);
				}
				
			}		
			
			if (silentM == 2)
				printByChar(board.getchar(exFX, exFY), exFX, exFY);			
				
			if(game_Mode!=3)
				pri.moveFruit(board.getWidth(),board.getLength(),direction);
			if (game_Mode == 2)
				Mysteps <<"f "<< direction <<' ';
			
			if (game_Mode == 3) {
				MystepsR >> ch;
				MystepsR >> ch;
				if (ch == 'U')
					pri.setY(pri.getY() - 1);
				else if (ch == 'D')
					pri.setY(pri.getY() + 1);
				else if (ch == 'R')
					pri.setX(pri.getX() + 1);
				else
					pri.setX(pri.getX() - 1);		

			}
		
		}
		/*If the ghost got stuck in one of the inner walls, we would return it to the previous location where it was*/
	    i = 0;
		for (int t = 0; t < numGhosts&&start; t++,i+=2)
		{
			if (board.checkIfHit(ARR[t]->getX(), ARR[t]->getY(), false, legendInFirstRow))
				setGhostCoor(*(ARR[t]), exGpoints[i], exGpoints[i + 1]);
		}
		if (board.checkIfHit(pri.getX(), pri.getY(), false, legendInFirstRow))
			setFruitCoor(pri, exFX, exFY);
		

		getAllCoor(pac, ARR, numGhosts, x_pac, y_pac, exGpoints, pri, exFX, exFY);

		i = 0;
		for (int m = 0; m < numGhosts; m++, i+= 2)
		{
			if (silentM == 2)
				ARR[m]->draw(exGpoints[i], exGpoints[i + 1]);			
				
		}
		
		changecoorFruit=pri.drawF(exFX, exFY,game_Mode,silentM);
		
		if (_kbhit())
		{
			dir = _getch();
			/*If the user presses ESC then the game will stop until he presses ESC again*/
			if (dir == 27) {
				if (game_Mode != 3)
				{
					clrscr();
					std::cout << "Game paused, press ESC again to continue";
					do {
						dir = _getch();
					} while (dir != 27);

					clrscr();
					board.printgame(_x, _y, x_legend, y_legend);
					printLivesAndPoints(pac.getLives(), pac.getPoints(), x_legend, y_legend);
				}
			}			
			start = true;
		}
		
		int newFruitPoint,xp, yp;
		if(game_Mode==3)
		{
			start = true;
			
			MystepsR >> dir;
			if (dir == 'B')
			{
				MystepsR >> newFruitPoint;

				pri.setPoint(newFruitPoint);
				MystepsR >> xp;
				MystepsR >> yp;
				gotoxy(exFX, exFY);
				if (silentM == 2)
					std::cout << board.getchar(exFX, exFY);
				
					
				pri.setX(xp);
				pri.setY(yp);
				MystepsR >> dir;
			}
			MystepsR >> dir;			

		}
		
		if (start)
			index++;
		/*If the Pacman ate from the food (advanced to a coordinate that had a point) we will update his number of points*/
		if (board.checkIfFoodCoor(x_pac, y_pac))
		{
			pac.setPoints();
			if (silentM == 2)
				printLivesAndPoints(pac.getLives(), pac.getPoints(), x_legend, y_legend);
			
		}
		if (silentM == 2)
			Delete(x_pac, y_pac);
		
		setPac(dir, Xdir, board, pac, legendInFirstRow,direction);
		
		checkdir(board.getWidth(),board.getLength(),board,pac, legendInFirstRow,  setMaxY,addy,silentM);

		getAllCoor(pac, ARR,  numGhosts, x_pac, y_pac, exGpoints, pri, exFX, exFY);

		char check[8];
		int numbertosee;int summall;
		/*If the Pacman hits one of the ghosts, we'll update his life and see if he's disqualified. If so we will finish the game*/
		for (int e = 0; e < numGhosts*2&&start; e+=2)
		{
			
				if (board.checkIfCrushed(x_pac, y_pac, exGpoints[e], exGpoints[e+1]))
				{
										
					Myresult << " death : " << counterdead;
					if (silentM == 1) {

						MyresultR >> check; MyresultR >> check; MyresultR >> numbertosee;
						if (numbertosee != (counterdead)) {
							std::cout << "Testing Faild" << std::endl;
							Sleep(4000);
							run = false;
						}
					}
					countertimegame += (counterdead);
					
					pac.setLives();
					
					printandsetStartPos(pac,  firstPos, board, numGhosts,ARR,silentM);

					if (pac.getLives() == 0)
					{
						
						run = false;
						Myresult << ' ' << countertimegame;
						if (silentM == 1) {
							MyresultR >> summall;							
							if (countertimegame != summall)
								std::cout << "Testing Faild" << std::endl;
							else
								std::cout << "Test passed" << std::endl;
							Sleep(4000);
						}
						countertimegame = 0;
					}
						
				}

		}		

		bool crush = board.checkIfCrushed(x_pac, y_pac, exFX, exFY);
		if (changecoorFruit ||crush)
		{
			if (crush)
			{
				pac.setPoints(pac.getPoints(), pri.getPoint());
				board.setMAXPOINTS(board.getMAXPOINTS(), pri.getPoint());
			}			

			gotoxy(exFX, exFY);
			if (silentM == 2)
				std::cout << board.getchar(exFX, exFY);
			if (game_Mode != 3)
			{
				board.RandFruit(pri, x_pac, y_pac);
				Mysteps <<"B "<<pri.getPoint()<<" "<< pri.getX() << ' ' << pri.getY() << ' ';
			}
					
			
		}
		if (game_Mode == 2 && start)
			Mysteps << "P " << direction << " ";
		
		if(start)
			counterdead++;
		if (pac.getPoints() == board.getMAXPOINTS())
		{
			pac.setPoints(0);
			Myresult << countertimegame;
			run = false;			
		}

		if (silentM == 2)
			Sleep(200);
	

	}
	for (int m = 0; m < 4; m++)//Releasing the array of pointers to the Ghosts
		delete ARR[m];
	Myresult.close();
	MyresultR.close();
	Mysteps.close();
	MystepsR.close();
	delete [] exGpoints;
	delete [] firstPos;
}

void Game::printByChar(char ch, int x, int y)
{
	gotoxy(x, y);
	std::cout << ch;
}


void Game::printLivesAndPoints(int lives, int points, int x_legend, int y_legend)
{
	gotoxy(x_legend, y_legend);
	std::cout << "Lives:" << lives;
	gotoxy(x_legend, y_legend+1);
	std::cout << "Points:" << points << std::endl;
}

void Game::Delete(int x, int y)
{
	gotoxy(x, y);
	std::cout << " ";
}

/*When one of the ghosts meets with the Pacman, we initialize everyone's positions in the game to their initial positions.*/
void Game::printandsetStartPos(Pacman& pac, int firstpos[],Board& board,int size,Ghost* ARR[],int silentM)
{

	char ch;
	gotoxy(pac.getX(), pac.getY());
	std::cout << ' ';
	pac.setX(firstpos[0]);
	pac.setY(firstpos[1]);
	int m = 2;
	for (int k = 0; k < size&&silentM==2; k++, m += 2)
	{
		
		gotoxy(ARR[k]->getX(), ARR[k]->getY());
		ch = board.getchar(ARR[k]->getX(), ARR[k]->getY());

		if (ch == '.')
			std::cout << '.';
		else
			std::cout << ' ';
	}
	m = 2;
	for (int k = 0; k < size; k++, m += 2)
	{
	
		ARR[k]->setX(firstpos[m]);
		ARR[k]->setY(firstpos[m + 1]);
	}

	
}



/*This function updates the coordinates of the pacman,Ghosts and fruit*/
void Game::getAllCoor(Pacman& pac, Ghost* ARR[],int numGhosts,int& x_pac, int& y_pac, int exGpoints[],Fruit& pri, int& exFX,int& exFY)
{

	x_pac = pac.getX();
	y_pac = pac.getY();
	int m = 0;
	for (int k = 0; k < numGhosts; k++,m+=2)
	{
	
		exGpoints[m] = ARR[k]->getX();
		exGpoints[m + 1] = ARR[k]->getY();

	}
	exFX = pri.getX();
	exFY = pri.getY();
}

void Game::setGhostCoor(Ghost& ghost, int x_ghost, int y_ghost)
{
	ghost.setX(x_ghost);
	ghost.setY(y_ghost);
}

void Game::setFruitCoor(Fruit& pri, int xF, int yF)
{
	pri.setX(xF);
	pri.setY(yF);
}

void  Game::setPac(char& dir, char& Xdir, Board& board, Pacman& pac, bool legendInFirstRow,char& direction)
{
	int x_pac = pac.getX();
	int y_pac = pac.getY();


	if (dir == 'W' || dir == 'w')
	{
		Xdir = dir;
		if (!(board.checkIfHit(x_pac, y_pac - 1, true, legendInFirstRow))) {
			pac.setY(y_pac - 1);
			direction = 'W';
		}
	}
	else if (dir == 'A' || dir == 'a')
	{
		Xdir = dir;
		if (!(board.checkIfHit(x_pac - 1, y_pac, true, legendInFirstRow))) {
			pac.setX(x_pac - 1);
			direction = 'A';
		}

	}
	else if (dir == 'D' || dir == 'd')
	{
		Xdir = dir;
		if (!(board.checkIfHit(x_pac + 1, y_pac, true, legendInFirstRow))) {
			pac.setX(x_pac + 1);
			direction = 'D';
		}
	}
	else if (dir == 'X' || dir == 'x')
	{
		Xdir = dir;
		if (!(board.checkIfHit(x_pac, y_pac + 1, true, legendInFirstRow))) {
			pac.setY(y_pac + 1);
			direction = 'X';
		}
	}
	else if (dir == 'S' || dir == 's')
	{
		pac.draw(x_pac, y_pac);
		do
		{
			dir = _getch();
		} while (dir != 'a' && dir != 'd' && dir != 'w' && dir != 'x' && dir != 'A' && dir != 'D' && dir != 'W' && dir != 'X' && dir != 27 && dir != 's');

	}

	/*If we didn't get a valid button the Pacman will continue in the direction he went the previous time (the last valid button)*/
	else {
		dir = Xdir;
		direction = toupper(dir);
	}
}

//The function stores the first coordinates of the creatures in appropriate places

void Game::initFirstPos(int firstPos[], int size, Pacman& pac,Ghost* ARR[])
{
	int ind = 0;

	firstPos[0] = pac.getX();
	firstPos[1] = pac.getY();

	for (int i = 2; i < size; i += 2)
	{
		
		firstPos[i] = ARR[ind]->getX();
		firstPos[i + 1] = ARR[ind++]->getY();
	}
}

/*This function checks whether the Pacman enters one of the internal tunnels.
If so she takes care to update his coordinate so that it comes out on the other side of the board*/
void Game::checkdir(int max_x, int max_y,Board& board,Pacman& pac, bool legendInFirstRow, bool& setMaxY, int addy, int silentM)
{
	int _x = pac.getX();
	int _y = pac.getY();
	int min_y = 1;
	if (legendInFirstRow)
	{
		max_x = max_x+1; 		
	}
	if (setMaxY)
		max_y += addy-2;

	if (_x > max_x - 2)
	{

		if ((board.getchar(_x, _y) == ' ' || board.getchar(_x, _y) == '.') && (board.getchar(0, _y) == ' ' || board.getchar(0, _y) == '.'))
			pac.setX(0);
		else if((board.getchar(_x, _y) == ' ' || board.getchar(_x, _y) == '.'))
			pac.setX(max_x - 1);
		else
			pac.setX(max_x - 2);
	}
	else if (_x < 1){
		
		if ((board.getchar(_x, _y) == ' ' || board.getchar(_x, _y) == '.') && (board.getchar(max_x - 1, _y) == ' ' || board.getchar(max_x - 1, _y) == '.'))
			pac.setX(max_x -2);
		else if ((board.getchar(_x, _y) == ' ') || (board.getchar(_x, _y) == '.'))
			pac.setX(0);
		else 
			pac.setX(1);
	
	}

	
	if (_y > max_y - 2)
	{	

		if ((board.getchar(_x, _y) == ' ' || board.getchar(_x, _y) == '.') && (board.getchar(_x, 0) == ' ' || board.getchar(_x, 0) == '.'))
			pac.setY(0);
		else if ((board.getchar(_x, _y) == ' ') || (board.getchar(_x, _y) == '.'))
			pac.setY(max_y - 1);
		else
			pac.setY(max_y - 2);


	}
	else if (_y < min_y)
	{
		if ((board.getchar(_x, _y) == ' ' || board.getchar(_x, _y) == '.') && (board.getchar(_x, max_y - 2) == ' ' || board.getchar(_x, max_y - 2) == '.'))
			pac.setY(max_y - 2);
		else if ((board.getchar(_x, _y) == ' ') || (board.getchar(_x, _y) == '.'))
			pac.setY(0);
		else
			pac.setY(1);

	}
	_x = pac.getX();
	_y = pac.getY();
	if(silentM==2)
		pac.draw(_x, _y);
}

