#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

class Game {
private:
	const int width = 80;	//do not change for now
	const int height = 20;

	int headx, heady;	//coordinates for head of snake
	int fruitx, fruity;		//coordinates for fruit coordinates

	int score;	//keeps track of player score

	int snakeTailx[100], snakeTaily[100];	//array of coordinates of snake tail
	int snakeTailLength;	//variable that stores length of snake tail

	enum snakeDirection { STOP = 0, Left, Right, Up, Down };	//snake movement directions
	snakeDirection sDir;	//variable for snake directions
public:
	void gameStart();	//used to start game
	std::string boardRender();	//renders board
	void updateGame();
	void input();

	bool isGameOver;	//checks if game is over
};