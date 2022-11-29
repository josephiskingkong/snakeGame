#include <iostream>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <fstream>

using namespace std;

struct leaderboard {
	string username;
	int score;
};

leaderboard leaderboardList[100];
fstream leaderboardFile;

void leaderboardOut(int leaderboardIndex) {
	cout << "           |" << leaderboardList[leaderboardIndex].username;
	for (int usernameSizeIndex = 0; usernameSizeIndex < 12 - leaderboardList[leaderboardIndex].username.size(); ++usernameSizeIndex) {
		cout << " ";
	}
	cout << " |" << leaderboardList[leaderboardIndex].score;
	ostringstream leaderboardScore;
	leaderboardScore << leaderboardList[leaderboardIndex].score;
	for (int scoreSizeIndex = 0; scoreSizeIndex < 4 - leaderboardScore.str().size(); ++scoreSizeIndex) {
		cout << " ";
	}
	cout << " |\n";
}

void colorize(int colorNumber) {
	HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorNumber);
}

void loading() {
	
	colorize(2);
	
	cout << "  ******** ****     **     **     **   ** ********\n";
	cout << "**////// /**/**   /**    ****   /**  ** /**///// \n";
	Sleep(300);
	system("cls");
	cout << "\n\n/**       /**//**  /**   **//**  /** **  /**      \n";
	cout << "*********/** //** /**  **  //** /****   /******* \n";
	Sleep(300);
	system("cls");
	cout << "\n\n\n\n////////**/**  //**/** **********/**/**  /**////  \n";
	cout << "       /**/**   //****/**//////**/**//** /**      \n";
	Sleep(300);
	system("cls");
	cout << "\n\n\n\n\n\n ******** /**    //***/**     /**/** //**/********\n";
	cout << "////////  //      /// //      // //   // //////// \n";
	Sleep(300);
	system("cls");
	Sleep(200);
	
	cout << "  ******** ****     **     **     **   ** ********\n";
	cout << " **////// /**/**   /**    ****   /**  ** /**///// \n";
	cout << "/**       /**//**  /**   **//**  /** **  /**      \n";
	cout << "/*********/** //** /**  **  //** /****   /******* \n";
	cout << "////////**/**  //**/** **********/**/**  /**////  \n";
	cout << "       /**/**   //****/**//////**/**//** /**      \n";
	cout << " ******** /**    //***/**     /**/** //**/********\n";
	cout << "////////  //      /// //      // //   // //////// \n";

	Sleep(200);
	
	colorize(7);
	
    cout << "\n          Press any button to continue...         ";
    
    if (getch()) {
    	system("cls");
    	colorize(2);
    	cout << "Enter your username (or enter 'resetscore if you want to reset leaderboard'): ";
	}

}

void gameOverScreen(string username, int score, int bestScore) {
	system("cls");
	
	colorize(4);
	
	cout << " @@@@@@@@   @@@@@@   @@@@@@@@@@   @@@@@@@@  \n";
	cout << "@@@@@@@@@  @@@@@@@@  @@@@@@@@@@@  @@@@@@@@  \n";
	cout << "!@@        @@!  @@@  @@! @@! @@!  @@!       \n";
	cout << "!@!        !@!  @!@  !@! !@! !@!  !@!       \n";
	cout << "!@! @!@!@  @!@!@!@!  @!! !!@ @!@  @!!!:!    \n";
	cout << "!!! !!@!!  !!!@!!!!  !@!   ! !@!  !!!!!:    \n";
	cout << ":!!   !!:  !!:  !!!  !!:     !!:  !!:       \n";
	cout << ":!:   !::  :!:  !:!  :!:     :!:  :!:       \n";
	cout << " ::: ::::  ::   :::  :::     ::    :: ::::  \n";
	cout << " :: :: :    :   : :   :      :    : :: ::   \n\n";
	cout << " @@@@@@   @@@  @@@  @@@@@@@@  @@@@@@@   \n";
	cout << "@@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@  \n";
	cout << "@@!  @@@  @@!  @@@  @@!       @@!  @@@  \n";
	cout << "!@!  @!@  !@!  @!@  !@!       !@!  @!@  \n";
	cout << "@!@  !@!  @!@  !@!  @!!!:!    @!@!!@!   \n";
	cout << "!@!  !!!  !@!  !!!  !!!!!:    !!@!@!    \n";
	cout << "!!:  !!!  :!:  !!:  !!:       !!: :!!   \n";
	cout << ":!:  !:!   ::!!:!   :!:       :!:  !:!  \n";
	cout << "::::: ::    ::::     :: ::::  ::   :::  \n";
	cout << " : :  :      :      : :: ::    :   : :  \n";
	colorize(64);
	cout << "\n                Your reslut:                \n";
	colorize(4);
	cout << "\n              Username: " << username << "  \n";
	cout << "                 Score: " << score << "        \n";
	cout << "            Best Score: " << bestScore << "  \n\n";
	colorize(7);
	
}

bool gameOver;
bool isUsernameInList;

const int width = 20;
const int height = 20;

int headX, headY, foodX, foodY, score;
int tailX[100], tailY[100];
int tailSize = 0;
int timeSleep = 150;
int sleepDeduction = 5;
int bestScore = 0;	
int rowCount = 0;

string str;
string username;
	
enum direction { STOP = 0, LEFT, RIGHT, DOWN, UP };
direction dir;

void setCursorPosition(int headX, int headY) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    COORD coord = { (SHORT)headX, (SHORT)headY };
    SetConsoleCursorPosition(hOut, coord);
}

void hideCursor () {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible - FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void setup() {
    gameOver = false;
    dir = STOP;
    headX = rand() % (width - 1) + 1;
    headY = rand() % (height - 1) + 1;
    score = 0;
    foodX = rand() % (width - 1) + 1;
    foodY = rand() % (height - 1) + 1;
}

void draw(string username, int bestScore) {
	
	hideCursor();
	
	
	
	for (int columnIndex = 0; columnIndex < width - 1; ++columnIndex) {
		setCursorPosition(columnIndex, 0);
		if (columnIndex == 0) cout << "\u2554";
		else {
			cout << "\u2550";
		}
		cout << "";
		cout.flush();		
	}
	cout << "\u2557" << endl;
	
	
	for (int columnIndex = 1; columnIndex < height; ++columnIndex) {
		for (int rowIndex = 0; rowIndex < width; ++rowIndex) {
			if (rowIndex == 0) {
				setCursorPosition(rowIndex, columnIndex);
				cout << "\u2551";
				cout << "";
				cout.flush();
			}
			
			if (columnIndex == headY && rowIndex == headX) {
				setCursorPosition(rowIndex, columnIndex);
				cout << "\u263A";
				cout << "";
				cout.flush();
				
			} else if (columnIndex == foodY && rowIndex == foodX) {
				colorize(96);
				setCursorPosition(rowIndex, columnIndex);
				cout << "\u2665";
				cout << "";
				cout.flush();
				colorize(2);
			} else {
				bool print = false;
				for (int tailIndex = 0; tailIndex < tailSize; ++tailIndex) {
					if (tailX[tailIndex] == rowIndex && tailY[tailIndex] == columnIndex) {
						setCursorPosition(rowIndex, columnIndex);
						cout << "\u2588";
						cout << "";
						cout.flush();						
						print = true;
					}
				}
				if (!print)
			    cout << " ";			
		    }
			if (rowIndex == width - 1) {
				setCursorPosition(rowIndex, columnIndex);
				cout << "\u2551";
				cout << "";
				cout.flush();
			}
		}
	    cout << endl;
	}
	cout << "\u255A";
	
	for (int columnIndex = 1; columnIndex < width - 1; ++columnIndex) {
		setCursorPosition(columnIndex, height);
		cout << "\u2550";
		cout << "";
		cout.flush();
	}
	cout << "\u255D";
	cout << "\n\n";
	cout << "+";
	for (int columnIndex = 0; columnIndex < 24; ++columnIndex) {
		cout << "-";
	}
	cout << "+";
	cout << endl;
	
	cout << "| Username: ";
	
	for (int columnIndex = 0; columnIndex <= 12; ++columnIndex) {
		if (username[columnIndex] != '\0') {
			colorize(96);
			cout << username[columnIndex];
			colorize(2);
		} else {
			cout << " ";
		}
	}
	cout << "|" << endl;
	
	ostringstream stringScore;
	stringScore << score;
	
	cout << "| Score: " << score;
	for (int columnIndex = 0; columnIndex < 16 - stringScore.str().size(); ++columnIndex) {
		cout << " ";
	}
	
	ostringstream stringBestScore;
	stringBestScore << bestScore;
	
	cout << "|" << endl;
	
	cout << "| Best Score: " << bestScore;
	for (int columnIndex = 0; columnIndex < 11 - stringBestScore.str().size(); ++columnIndex) {
		cout << " ";
	}
	
	cout << "|" << endl;
	cout << "+";
	for (int columnIndex = 0; columnIndex < 24; ++columnIndex) {
		cout << "-";
	}
	cout << "+";
}

void input() {
        if(GetAsyncKeyState(VK_UP) && dir != DOWN) {
            dir = UP;
        }
        if(GetAsyncKeyState(VK_DOWN) && dir != UP) {
            dir = DOWN;
        }
        if(GetAsyncKeyState(VK_LEFT) && dir != RIGHT) {
            dir = LEFT;
        }
        if(GetAsyncKeyState(VK_RIGHT) && dir != LEFT) {
            dir = RIGHT;
        }
    }

void logic() {
	
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prevNewX;
	int prevNewY;
	tailX[0] = headX;
	tailY[0] = headY;
	
	for (int tailIndex = 1; tailIndex < tailSize; ++tailIndex) {
		prevNewX = tailX[tailIndex];
		prevNewY = tailY[tailIndex];
		tailX[tailIndex] = prevX;
		tailY[tailIndex] = prevY;
		prevX = prevNewX;
		prevY = prevNewY;
	}
	switch(dir) {
		case LEFT:
			--headX;
			break;
		case RIGHT:
			++headX;
		    break;
		case UP:
			--headY;
		    break;
		case DOWN:
			++headY;
		    break;
		default:
		    break;	
	}
	
	if (headX > width - 2 || headX <= 0 || headY > height - 1 || headY <= 0 ) {
		gameOver = true;
	}
	for (int tailIndex = 0; tailIndex < tailSize; ++tailIndex) {
		if (tailX[tailIndex] == headX && tailY[tailIndex] == headY) {
			gameOver = true;
		}
	}
	if (headX == foodX && headY == foodY) {
		score += 1;
		if (score > bestScore) {
		    bestScore = score;
	    }
		timeSleep = timeSleep - sleepDeduction;
		if (timeSleep <= 75) {
			sleepDeduction = 0;
		}
		foodX = rand() % width;
        foodY = rand() % height;
        ++tailSize;
	}
}
void sorting(int rowCount) {
	for (int leaderboardIndex = 0; leaderboardIndex < rowCount; ++leaderboardIndex) {
	int tmp = 0;
	string tmpUsername;
	if (leaderboardList[leaderboardIndex].score < leaderboardList[leaderboardIndex + 1].score) {
		tmp = leaderboardList[leaderboardIndex].score;
		leaderboardList[leaderboardIndex].score = leaderboardList[leaderboardIndex + 1].score;
		leaderboardList[leaderboardIndex + 1].score = tmp;
		tmpUsername = leaderboardList[leaderboardIndex].username;
		leaderboardList[leaderboardIndex].username = leaderboardList[leaderboardIndex + 1].username;
		leaderboardList[leaderboardIndex + 1].username = tmpUsername;
		leaderboardIndex = 0;
		}
	}
}

void clearingLeaderboard(string username) {
	colorize(160);
	cout << "\nLeaderboard successfully reset!";
	ofstream leaderboardFileCleaner;
	leaderboardFileCleaner.open("leaderboard.txt", std::ofstream::out | std::ofstream::trunc);
	leaderboardFileCleaner.close();	
	colorize(2);
	cout << "\nEnter your username: ";
}

void writeInLeaderboard() {
	leaderboardFile.open("leaderboard.txt");
	for (int leaderboardIndex = 0; leaderboardIndex < rowCount; ++leaderboardIndex) {
		leaderboardFile >> leaderboardList[leaderboardIndex].username;
		leaderboardFile >> leaderboardList[leaderboardIndex].score;
	}
	leaderboardFile.close();	
}

int main() {
	system("chcp 65001");
	system("cls");
	
	loading();
	
	start:
	
	colorize(96);
	cin >> username;
	colorize(2);
	
	if (username == "resetscore") {
        clearingLeaderboard(username);
		goto start;
	}

	leaderboardFile.open("leaderboard.txt");
	if(!leaderboardFile.is_open()) {
		cout << "File 'leaderboard.txt' not found!";
		system("pause");
		return 0;
	}

	while(getline(leaderboardFile, str)) {
		++rowCount;
	}
	leaderboardFile.close();
	
	writeInLeaderboard();
	
	for (int leaderboardIndex = 0; leaderboardIndex < rowCount; ++leaderboardIndex) {
		if (username == leaderboardList[leaderboardIndex].username) {
			bestScore = leaderboardList[leaderboardIndex].score;
		}
	}
	
	if (username.size() > 10) {
		colorize(4);
		cout << "\nWrong username, it should be less then 10 symbols\n";
		colorize(2);
		cout << "\nEnter your username: ";
		goto start;
	}
	colorize(2);
	
	system("cls");

	setup();
	while(!gameOver) {
		input();
		logic();
		draw(username, bestScore);
		Sleep(timeSleep);
	}
    
	if (gameOver) {
		gameOverScreen(username, score, bestScore);
	}
	
	for (int leaderboardIndex = 0; leaderboardIndex < rowCount; ++leaderboardIndex) {
		if (leaderboardList[leaderboardIndex].username == username || 
		leaderboardList[leaderboardIndex].username == username && score > leaderboardList[leaderboardIndex].score) {
			leaderboardList[leaderboardIndex].score = bestScore;
			isUsernameInList = true;
		}
	}
	if (!isUsernameInList) {
		leaderboardList[rowCount].username = username;
		leaderboardList[rowCount].score = score;
	}
	
    sorting(rowCount);
    sorting(rowCount);

	ofstream leaderboardFileCleaner;
	leaderboardFileCleaner.open("leaderboard.txt", std::ofstream::out | std::ofstream::trunc);
	leaderboardFileCleaner.close();
	
	leaderboardFile.open("leaderboard.txt");
	leaderboardFile << leaderboardList[0].username << " " << leaderboardList[0].score << "\n";
	for (int leaderboardIndex = 1; leaderboardIndex < rowCount + 1; ++leaderboardIndex) {
		leaderboardFile << leaderboardList[leaderboardIndex].username << " " << leaderboardList[leaderboardIndex].score << "\n";
	}

	colorize(6);
	cout << "               Best results\n\n";
	for (int leaderboardIndex = 0; leaderboardIndex < 10; ++leaderboardIndex) {
		leaderboardOut(leaderboardIndex);
	}
	colorize(0);
	
	system("pause");
}
