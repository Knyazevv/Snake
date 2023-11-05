#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;   // score счетчик;
int tailX[100], tailY[100];
int nTail;

enum direction
{
	STOP = 0, LEFT, RIGHT, UP, DOWN
};
direction  dir;



void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

}


void Draw()
{
	system("cls");
	cout << "Press:      'W' 'A' 'S' 'D' to play"<<endl;
	cout << "                     OR"<<endl;
	cout << "            'LEFT' 'RIGHT' 'UP' 'DOWN'"<<endl;
	cout << "Press:      'Q' to end game"<<endl;

	cout << "__________________________________________"<<endl;
	cout << endl;
	cout << "                Your SCORE: " << score << endl;

		

	for (size_t i = 0; i < width+1; i++) 
	{
		if (i==0)
		{
			cout << char(201);
		}
		if (i==40)
		{
			cout << char(187);
		}
		if (i == 1 || i < width)
		{
		cout << char(205);
		}
	}
		cout << endl;


	for (size_t i = 0; i < height+1; i++)
	{
		for (size_t j = 0; j < width+1; j++)
		{

			if (j == 0 || j == width)
				cout << (char)186;


			if (i == y && j == x)
				cout << (char)220;
			

			else if (i == fruitY && j == fruitX)
				cout << "G";

			else
			{
				bool print = false;
				for (size_t k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						if (print)
						cout << (char)220;

					}
				}

				if (!print)
				cout << " ";
		}
		}
		cout << endl;
	}
	/*
	for (size_t i = 0; i < width+1; i++)
	{
		if (i == 0)
		{
			cout << char(200);
		}
		if (i == 40)
		{
			cout << char(188);
		}
		if (i == 1 || i < width)
		{
			cout << char(205);
		}

	}
	*/

	cout << endl;
	Sleep(350);
}


void Input()
{
	if (_kbhit())
	{
	switch (_getch())
	{
	case 'q': case 'Q':
		gameOver=true;
	case 'a': case 'A': case 75:
	if (dir != RIGHT)
	dir = LEFT;
		break;
	case 's': case 'S': case 80:
	if (dir != UP)
	dir = DOWN;
		break;
	case 'd': case 'D': case 77:
	if (dir != LEFT)
	dir = RIGHT;
		break;
	case 'w': case 'W': case 72:
	if (dir != DOWN)
	dir = UP;
		break;
		}
		}
}


void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (size_t i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	/*
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	*/
	if (x >= width)
		x = 0;
	else if (x < 0)
		x = width - 1;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (size_t i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver=true;
	}


	if (x == fruitX && y == fruitY)
	{
		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
	if (gameOver == true)
		cout << "                 Game over" << endl;
}


int main()
{
	srand(unsigned(time(0)));

	Setup();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}

	
	return 0;
}
