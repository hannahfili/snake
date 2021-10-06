#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

int fruitX = 0;
int fruitY = 0;
int locationLength = 0;
const int n = 20;
const float frameDelay = 300;
struct vec2 {
	int x;
	int y;
};


bool isUpPressed();

bool isDownPressed();

bool isLeftPressed();

bool isRightPressed();
bool updateSnake(vec2*, bool**, bool**, string, bool);


void setInitialCoordinates(vec2*, int, bool**, bool**);
void drawBoard(vec2*, bool**, bool**);
bool updateFruit(vec2*, bool**, bool**);
vec2* changeSize(vec2*);
void addTail(vec2*, vec2);
vec2 getTailCoordinates(vec2*);

void drawBoard(vec2* location, bool** board, bool** fruitBoard) {
	char symbol = 207;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (fruitBoard[i][j] == true) {

				//cout << "board[" << i << "][" << j << "]" << endl;
				cout << symbol;
			}
			else if (board[i][j] == true) {
				cout << "*";
			}

			else
				cout << " ";
		}
		cout << endl;
	}
}
vec2 getTailCoordinates(vec2* location) {
	return location[locationLength - 1];
}
void addTail(vec2* location, vec2 tailCoordinates) {
	location[locationLength - 1].x = tailCoordinates.x;
	location[locationLength - 1].y = tailCoordinates.y;
}
bool updateFruit(vec2* location, bool** board, bool** fruitBoard) {
	//cout << "fruitboard: " << fruitX << " ! " << fruitY << endl;
	//cout << "fruitboard[x][y] " << fruitBoard[fruitX][fruitY] << endl;
	
	bool longer = false;

	//cout << "locationLength: " << locationLength << endl;
	//getchar();


	for (int i = 0; i < locationLength-1; i++) {
		if (fruitBoard[location[i].x][location[i].y]) {
			fruitBoard[location[i].x][location[i].y] = false;
			while (true) {
				fruitX = rand() % 11;
				fruitY = rand() % 11;
				if (board[fruitX][fruitY] == false) {
					fruitBoard[fruitX][fruitY] = true;
					longer = true;
					break;
				}
			}
		}
	}
	//cout << "fruitboard2: " << fruitX << " ! " << fruitY << endl;
	//cout << "fruitboard2[x][y] " << fruitBoard[fruitX][fruitY] << endl;
	return longer;
	
}
int main()
{
	//tablica 2wym 10x10
	//3 segmentow
	//
	string previousDirection = "down";
	string currentDirection = "down";
	int counter = 0;
	bool end = false;
	bool longer = false;
	bool** board = new bool* [n];
	bool** fruitBoard = new bool* [n];
	locationLength = 3;
	vec2* location = new vec2[locationLength];
	vec2 tailCoordinates;
	tailCoordinates.x = 0;
	tailCoordinates.y = 0;
	srand(time(NULL));
	

	for (int i = 0; i < n; i++) {
		board[i] = new bool[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = false;
		}
	}
	for (int i = 0; i < n; i++) {
		fruitBoard[i] = new bool[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fruitBoard[i][j] = false;
		}
	}

	double frameTime = 0;
	double start = 0, stop = 0;

	while (!end) {
		
		start = 1.0* clock() / CLOCKS_PER_SEC * 1000;

		if (counter == 0) {
			setInitialCoordinates(location, counter, board, fruitBoard);
			//cout << counter << endl;
			//getchar();
		}

		if (frameTime > frameDelay) {
			system("cls");
			end = updateSnake(location, board, fruitBoard, currentDirection, longer);
			if (longer) {
				//tailCoordinates = getTailCoordinates(location);
				location = changeSize(location);
				//addTail(location, tailCoordinates);

				/*cout << "\nupdateSnake:\n";
				for (int i = 0; i < locationLength; i++) {
					cout << "location[" << i << "].x:" << location[i].x << endl;
					cout << "location[" << i << "].y:" << location[i].y << endl;
				}*/
			}
			//cout << "MAIN: location[0].x/y:" << location[0].x << " / " << location[0].y << endl;
			//getchar();
			longer=updateFruit(location, board, fruitBoard);
			//cout << "locationLength z MAIN: " << locationLength << endl;
			/*for (int i = 0; i < locationLength; i++) {
				
				cout << "first location: " << location[i].x << " ! " << location[i].y << endl;
			}*/
			drawBoard(location, board, fruitBoard);
			frameTime = 0;
		}

		//getchar();
		
		/*cout << "previousDirection: " << previousDirection << endl;
				cout << "currentDirection: " << currentDirection << endl;*/
		//getchar();
		
		if (isUpPressed()) {
			/*cout << "UP\n";
			getchar();*/
			if (currentDirection != "down") {
				previousDirection = currentDirection;
				currentDirection = "up";
				//cout << "previousDirection: " << previousDirection << endl;
				//cout << "currentDirection: " << currentDirection << endl;
			}
		}

		else if (isLeftPressed()) {
			/*cout << "LEFT\n";
			getchar();*/

			if (currentDirection != "right") {
				previousDirection = currentDirection;
				currentDirection = "left";
				//cout << "previousDirection: " << previousDirection << endl;
				//cout << "currentDirection: " << currentDirection << endl;
			}

		}

		else if (isRightPressed()) {
			/*cout << "RIGHT\n";
			getchar();*/

			if (currentDirection != "left") {
				previousDirection = currentDirection;
				currentDirection = "right";
				//cout << "previousDirection: " << previousDirection << endl;
				//cout << "currentDirection: " << currentDirection << endl;
			}
		}

		else if (isDownPressed()) {
			//cout << "DOWN\n";
			//getchar();
			if (currentDirection != "up") {
				previousDirection = currentDirection;
				currentDirection = "down";
				//cout << "previousDirection: " << previousDirection << endl;
				//cout << "currentDirection: " << currentDirection << endl;
			}
		}
		
		stop = 1.0*clock() / CLOCKS_PER_SEC * 1000;

		frameTime += stop - start;

		//getchar();
		counter++;
	}
}

vec2* changeSize(vec2* coordinatesTable) {

		vec2* newArray = new vec2[locationLength + 1];
		for (int i = 0; i < locationLength; i++) {
			newArray[i] = coordinatesTable[i];
		}
		newArray[locationLength].x = 5;
		newArray[locationLength].y = 5;
		locationLength++;

		delete[] coordinatesTable;
		return newArray;
	

}

bool updateSnake(vec2* location, bool** board, bool** fruitBoard, string currentDirection, bool longer) {
	
	for (int i = locationLength - 1; i >= 1; i--) {
		location[i].x = location[i - 1].x;
		//cout << "location[" << i << "].x:" << location[i].x << endl;
		location[i].y = location[i - 1].y;
		//cout << "location[" << i << "].y:" << location[i].y << endl;
	}
	
	bool meetSnake = false;
	if (currentDirection == "right") {
		if (location[0].y + 1 < n) {
			for (int i = 1; i < locationLength; i++) {
				if (location[0].y + 1 == location[i].y && location[0].x==location[i].x) {
					meetSnake = true;
					break;
				}
			}
			if (!meetSnake) {
				location[0].y += 1;
			}
			else return true;
		}
			
		else return true;
	}
	else if (currentDirection == "left") {
		
		if (location[0].y - 1 >= 0) {
			for (int i = 1; i < locationLength; i++) {
				if (location[0].y - 1== location[i].y && location[0].x==location[i].x) {
					meetSnake = true;
					break;
				}
			}
			if (!meetSnake) {
				location[0].y -= 1;
			}
			else return true;
		}
			
		else return true;
	}
	else if (currentDirection == "down") {
		if (location[0].x + 1 < n) {
			for (int i = 1; i < locationLength; i++) {
				if (location[0].x + 1==location[i].x && location[0].y==location[i].y) {
					meetSnake = true;
					break;
				}
			}
			if (!meetSnake) {
				location[0].x += 1;
			}
			else return true;
		}
			
		else return true;

	}
	else if (currentDirection == "up") {
		if (location[0].x - 1 >= 0) {
			for (int i = 1; i < locationLength; i++) {
				if (location[0].x - 1==location[i].x && location[0].y==location[i].y) {
					meetSnake = true;
					break;
				}
			}
			if (!meetSnake) {
				location[0].x -= 1;
			}
			else return true;
		}
			
		else return true;

	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = false;
		}
	}

	
	
	for (int i = 0; i < locationLength; i++) {
		board[location[i].x][location[i].y] = true;
	}

	//cout << "after:" << endl;
	//cout << "location[0].x/y:" << location[0].x << " / " << location[0].y << endl;
	
	//getchar();
	return false;

}

void setInitialCoordinates(vec2* location, int counter, bool** board, bool** fruitBoard) {

	int length = 3;

	for (int i = 0; i < length; i++) {
		location[i].y = n / 2;
	}
	location[0].x = n/2;
	location[1].x = n / 2 - 1;
	location[2].x = n / 2 - 2;


	//cout << length;

	for (int i = 0; i < length; i++) {
		board[location[i].x][location[i].y] = true;
		//cout << location[i].x << " ! " << location[i].y << endl;
	}
	
	while (true) {
		fruitX = rand() % 11;
		fruitY = rand() % 11;
		if (board[fruitX][fruitY] == false) {
			break;
		}
	}
	

	char symbol = 207;

	fruitBoard[fruitX][fruitY] = true;
	board[fruitX][fruitY] = true;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == true && fruitBoard[i][j]==true) {

				//cout << "board[" << i << "][" << j << "]" << endl;
				cout << symbol;
			}
			else if (board[i][j] == true) {
				cout << "*";
			}

			else
				cout << " ";
		}
		cout << endl;
	}


	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == true)
				cout << "[" << i << "] [" << j << "]" << endl;
		}
	}
	cout << "initialised******************************" << endl;
		getchar();*/
}

bool isUpPressed() {
	return GetKeyState(VK_UP) & 0x8000;
}

bool isDownPressed() {
	return GetKeyState(VK_DOWN) & 0x8000;
}

bool isLeftPressed() {
	return GetKeyState(VK_LEFT) & 0x8000;
}

bool isRightPressed() {
	return GetKeyState(VK_RIGHT) & 0x8000;
}