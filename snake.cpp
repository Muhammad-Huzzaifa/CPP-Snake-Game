#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>

using namespace std;

const int HEIGHT = 22;                 // Actual 20 rows and extra 2 rows for border
const int WIDTH = 22;                  // Actual 20 columns and extra 2 columns for border
int headX, headY;                      // Variables that controls the head of the snake
int fruitX, fruitY;                    // Variables controlling the food appearance
int score;                             // Current score of the game
int nTail;                             // Length of the snake
int key = 2;                           // Key variable purpose to take the input, and initially the snake starts moving right
bool gameOver;                         // Bool variable that becomes true when the game is over for any purpose
int tailX[(HEIGHT - 2) * (WIDTH - 2)]; // Array that controls the x-position of the snake's tale at every point
int tailY[(HEIGHT - 2) * (WIDTH - 2)]; // Array that controls the y-position of the snake's tale at every point
char gameMap[HEIGHT][WIDTH + 1] = { }; // 2D-character array representing the game map

void hideCursor();                     // Hide the cursor to make the console screen clear
void initializingVariables();          // All variables initial declaration before starting of game
void initializeAndDisplayMap();        // Function that stores the values in character array and display it on console 
void mainLogic();                      // Function takes the input, moves the snake, eat the food, update the score, and over the game

int main()
{
	initializingVariables();       // All variables initial declaration before starting of game

	while (!gameOver)
	{
		initializeAndDisplayMap(); // Function to store the values in character array and display it on console after every update
		mainLogic();               // Controls the main logic of the game
		Sleep(50);                 // Sleep to make the game playable
	}

	system("pause");
	return 0;
}

// Function to hide the console cursor
void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info{};
	info.dwSize = HEIGHT * WIDTH;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void initializingVariables()
{
	srand(time(0));
	
	// Initially the snake is at the middle of the map
	headX = WIDTH / 2;
	headY = HEIGHT / 2;

	// Generate the food at that position that is empty
	do {
		fruitX = rand() % (WIDTH - 2) + 1;
		fruitY = rand() % (HEIGHT - 2) + 1;
	} while (!gameMap[fruitX][fruitY] == ' ');

	score = 0;        // Initially the score is 0
	nTail = 0;        // Initially length of snake is 1 but due to the fact that array starts from 0 index, so its value is zero
	gameOver = false; // Initially the game over is false

}

void initializeAndDisplayMap()
{
	system("cls"); // Function to clear the screen

	// Storing the values in the character array
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			// Boundary line shaping
			if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
				gameMap[i][j] = '.';

			// Snake Head
			else if (i == headY && j == headX)
				gameMap[i][j] = 'O';

			// Fruit
			else if (i == fruitY && j == fruitX)
				gameMap[i][j] = '*';

			// Snake's Tail
			else
			{
				bool printTail = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailY[k] == i && tailX[k] == j)
					{
						gameMap[i][j] = 'o';
						printTail = true;
					}
				}

				// Remaining is filled with space
				if (!printTail)
					gameMap[i][j] = ' ';
			}

		}
	}

	// Cyan color for game bar
	cout << "\033[36m" << "Score: " << score << endl;

	// Display the 2D-character array on the the console
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			hideCursor();
			// Cyan color for boundary lines
			if (gameMap[i][j] == '.')
				cout << "\033[36m" << gameMap[i][j] << " ";

			// Green color with slightly different shade is for the head of snake
			else if (gameMap[i][j] == 'O')
				cout << "\033[92m" << gameMap[i][j] << " ";

			// Green color for snake body
			else if (gameMap[i][j] == 'o')
				cout << "\033[32m" << gameMap[i][j] << " ";

			// Yellow color for food pills
			else if (gameMap[i][j] == '*')
				cout << "\033[33m" << gameMap[i][j] << " ";

			// Reset the color else
			else
				cout << "\033[0m" << gameMap[i][j] << " ";
		}
		cout << endl;
	}
}

void mainLogic()
{
	// Snake movement by storing its x & y co-ordinates of previous positions
	int back1X = tailX[0];
	int back1Y = tailY[0];
	int back2X, back2Y;
	tailX[0] = headX;
	tailY[0] = headY;

	for (int i = 1; i < nTail; i++)
	{
		back2X = tailX[i];
		back2Y = tailY[i];
		tailX[i] = back1X;
		tailY[i] = back1Y;
		back1X = back2X;
		back1Y = back2Y;
	}

	// User input for snake movement
	if (_kbhit())
	{
		switch (_getch())
		{
		// Left arrow key
		case 75:
			if (key == 2)
				key = 2;
			else
				key = 1;
			break;

		// Right arrow key
		case 77:
			if (key == 1)
				key = 1;
			else
				key = 2;
			break;

		// Up arrow key
		case 72:
			if (key == 4)
				key = 4;
			else
				key = 3;
			break;

		// Down arrow key
		case 80:
			if (key == 3)
				key = 3;
			else
				key = 4;
			break;

		// For exiting the game
		case 'q':
		case 'Q':
			key = 0;
			break;

		default:
			break;
		}
	}

	// Movement according to the key value which is change when any movement key is pressed
	switch (key)
	{
	case 1:
		headX--;
		break;
	case 2:
		headX++;
		break;
	case 3:
		headY--;
		break;
	case 4:
		headY++;
		break;
	}

	// If snake reaches the left and right boundary lines then it appears from the opposite side
	if (headX == 0)
		headX = WIDTH - 2;
	else if (headX == WIDTH - 1)
		headX = 1;

	// If snake reaches the up and down boundary lines then it appears from the opposite side
	if (headY == 0)
		headY = HEIGHT - 2;
	else if (headY == HEIGHT - 1)
		headY = 1;

	// Snake can die if it touches his own body
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == headX && tailY[i] == headY)
			gameOver = true;

	// Score updating after eating the food and generating another food in the valid position
	if (headX == fruitX && headY == fruitY)
	{
		score += 1;
		do {
			fruitX = rand() % (WIDTH - 2) + 1;
			fruitY = rand() % (HEIGHT - 2) + 1;
		} while (!gameMap[fruitX][fruitY] == ' ');

		// Snake size increases after eating the food pills by one
		nTail++;
	}
}