#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <time.h>
using namespace std;

class Game {
private:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool appleRight = false;	//paramaters to pass into ai, indicates which direction the snake needs to turn, not actual position relative to snake
		bool appleAhead = false;
		bool dangerRight = false;	//only test for danger in squares adjacent to snake head
		bool dangerLeft = false;
		bool dangerAhead = false;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	void getApplePos();	//gets position of apple relative to snake head
};