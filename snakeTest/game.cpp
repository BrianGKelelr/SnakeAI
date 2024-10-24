#include "game.hpp"

void Game::gameStart() {	//used to start game
	srand (time(0));
	isGameOver = false;
	sDir = Up;			//stops player movement
	headx = width / 2;		//puts snake in middle of game board
	heady = height / 2;
	fruitx = rand() % width;	//randomly places fruit
	fruity = rand() % height;
	score = 0;		//resets score
	snakeTailLength = 0;	//sets snake length to 0
	getApplePos();
};

std::string Game::boardRender() {
	system("cls");	//clears the console
	std::string output;

	for (int i = 0; i < width + 2; i++) {	//sets up top wall using "-" character
		output += "-";
	}
	output += "\n";

	for (int i = 0; i < height; i++) {		//goes through game board one row at a time to print everything
		for (int j = 0; j <= width; j++) {	//sets up side walls with "|" character
			if (j == 0 || j == width) {
				output += "|";
			}
			if (i == heady && j == headx) {		//if current printing coordinate equals coordinates of snake head, print snake head
				output += "O";
			}
			else if (i == fruity && j == fruitx) {	//prints fruit (money) if coordinates equal coordinates of fruit
				output += "$";
			}
			else {	//snake body
				bool prTail = false;
				for (int k = 0; k < snakeTailLength; k++) {
					if (snakeTailx[k] == j && snakeTaily[k] == i) {
						output += "o";
						prTail = true;	//sets prTail to true to avoid infinite loop
					}
				}
				if (!prTail) {		//prints empty space if not a wall, fruit, or snake
					output += " ";
				}
			}
		}
		output += "\n";
	}
	for (int i = 0; i < width + 2; i++) {	//sets up bottom wall using "-" character
		output += "-";
	}
	output += "\n";

	output = output + "Score: " + to_string(score) + "\n";	//prints score
	return output;
};

void Game::updateGame() {
	getWallPos();
	AImoveSnake();	//uses our algorithm to move the snake

	int prevx = snakeTailx[0];
	int prevy = snakeTaily[0];
	int prev2x, prev2y;
	snakeTailx[0] = headx;
	snakeTaily[0] = heady;

	for (int i = 1; i < snakeTailLength; i++) {		//moves snake parts forward
		prev2x = snakeTailx[i];
		prev2y = snakeTaily[i];
		snakeTailx[i] = prevx;
		snakeTaily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}

	switch (sDir) {		//gets input from sDir and moves snake accordingly
	case Left:
		headx--;
		break;
	case Right:
		headx++;
		break;
	case Up:
		heady--;
		break;
	case Down:
		heady++;
		break;
	}

	if (headx >= width || headx < 0 || heady >= height || heady < 0) {	//if you go out of bounds you die
		isGameOver = true;
	}

	for (int i = 0; i < snakeTailLength; i++) {		//if snake collides with body, game over
		if (snakeTailx[i] == headx && snakeTaily[i] == heady) {
			isGameOver = true;
		}
	}

	if (headx == fruitx && heady == fruity) {	//if snake eats food, increase length and score
		score++;
		fruitx = rand() % width;
		fruity = rand() % height;
		for (int i = 0; i < snakeTailLength; i++) {
			if (snakeTailx[i] == fruitx && snakeTaily[i] == fruity) {
				fruitx = rand() % width;
				fruity = rand() % height;
			}
			else {
				i = snakeTailLength;
			}
		}
		snakeTailLength += 1;
	}
	//std::cout << " Right: " << appleRight << "\nLeft: " << appleLeft << "\nAhead: " << appleAhead;	//used to make sure the left, right, and ahead apple positions are working
	//std::cout << "DangerRight: " << dangerRight << "\nDangerLeft: " << dangerLeft << "\ndangerAhead: " << dangerAhead;
};

void Game::input() {
	if (_kbhit()) {		//checks to see if a key was pressed
		switch (_getch()) {		//gets the key that was pressed
		case 'a':
			sDir = Left;
			break;
		case 'd':
			sDir = Right;
			break;
		case 'w':
			sDir = Up;
			break;
		case 's':
			sDir = Down;
			break;
		case 'x':				//if x is pressed, ends game
			isGameOver = true;
			break;
		}
	}
};

void Game::getApplePos() {
	int x = headx - fruitx;
	int y = heady - fruity;
	switch (sDir) {		//gets input from sDir
	case Left:
		if (x > 0 && y > 0) {
			appleRight = true;
			appleAhead = true;
			appleLeft = false;
		}
		else if (x > 0 && y < 0) {
			appleRight = false;
			appleAhead = true;
			appleLeft = true;
		}
		else if (x <= 0 && y > 0) {
			appleRight = true;
			appleAhead = false;
			appleLeft = false;
		}
		else if (x <= 0 && y < 0) {
			appleRight = false;
			appleAhead = false;
			appleLeft = true;
		}
		else if (x > 0 && y == 0) {
			appleRight = false;
			appleAhead = true;
			appleLeft = false;
		}
		else if (x < 0 && y == 0) {
			appleRight = false;
			appleAhead = false;
			appleLeft = false;
		}
		break;
	case Right:
		if (x >= 0 && y > 0) {
			appleRight = false;
			appleAhead = false;
			appleLeft = true;
		}
		else if (x >= 0 && y < 0) {
			appleRight = true;
			appleAhead = false;
			appleLeft = false;
		}
		else if (x < 0 && y > 0) {
			appleAhead = true;
			appleRight = false;
			appleLeft = true;
		}
		else if (x < 0 && y < 0) {
			appleRight = true;
			appleAhead = true;
			appleLeft = false;
		}
		else if (x < 0 && y == 0) {
			appleRight = false;
			appleAhead = true;
			appleLeft = false;
		}
		else if (x > 0 && y == 0) {
			appleRight = false;
			appleAhead = false;
			appleLeft = false;
		}
		break;
	case Up:
		if (x > 0 && y > 0) {
			appleRight = false;
			appleAhead = true;
			appleLeft = true;
		}
		else if (x > 0 && y <= 0) {
			appleRight = false;
			appleAhead = false;
			appleLeft = true;
		}
		else if (x < 0 && y > 0) {
			appleRight = true;
			appleAhead = true;
			appleLeft = false;
		}
		else if (x < 0 && y <= 0) {
			appleRight = true;
			appleAhead = false;
			appleLeft = false;
		}
		else if (x == 0 && y > 0) {
			appleRight = false;
			appleAhead = true;
			appleLeft = false;
		}
		else if (x == 0 && y < 0) {
			appleRight = false;
			appleAhead = false;
			appleLeft = false;
		}
		break;
	case Down:
		if (x > 0 && y >= 0) {
			appleRight = true;
			appleAhead = false;
			appleLeft = false;
		}
		else if (x > 0 && y < 0) {
			appleRight = true;
			appleAhead = true;
			appleLeft = false;
		}
		else if (x < 0 && y >= 0) {
			appleRight = false;
			appleAhead = false;
			appleLeft = true;
		}
		else if (x < 0 && y < 0) {
			appleRight = false;
			appleAhead = true;
			appleLeft = true;
		}
		else if (x == 0 && y > 0) {
			appleRight = false;
			appleAhead = false;
			appleLeft = false;
		}
		else if (x == 0 && y < 0) {
			appleRight = false;
			appleAhead = true;
			appleLeft = false;
		}
		break;
	}
};

void Game::getWallPos() {
	int negX = headx--;
	int posX = headx++;
	int negY = heady--;
	int posY = heady++;

	dangerRight = false;
	dangerLeft = false;
	dangerAhead = false;
	switch (sDir) {		//gets input from sDir
	case Left:
		for (int i = 0; i < snakeTailLength; i++) {		
			if (snakeTailx[i] == headx  && snakeTaily[i] == heady-1) {
				dangerRight = true;
			}
			if (snakeTailx[i] == headx && snakeTaily[i] == heady + 1) {
				dangerLeft = true;
			}
			if (snakeTailx[i] == headx -1 && snakeTaily[i] == heady) {
				dangerAhead = true;
			}
		}
		if (headx-1 == -1) {
			dangerAhead = true;
		}
		if (heady-1 == -1) {
			dangerRight = true;
		}
		if (heady+1 == height) {
			dangerLeft = true;
		}
		break;
	case Right:
		for (int i = 0; i < snakeTailLength; i++) {
			if (snakeTailx[i] == headx && snakeTaily[i] == heady - 1) {
				dangerLeft = true;
			}
			if (snakeTailx[i] == headx && snakeTaily[i] == heady + 1) {
				dangerRight = true;
			}
			if (snakeTailx[i] == headx +1 && snakeTaily[i] == heady) {
				dangerAhead = true;
			}
		}
		if (headx+1 == width) {
			dangerAhead = true;
		}
		if (heady-1 == -1) {
			dangerLeft = true;
		}
		if (heady+1 == height) {
			dangerRight= true;
		}
		break;
	case Up:
		for (int i = 0; i < snakeTailLength; i++) {
			if (snakeTailx[i] == headx && snakeTaily[i] == heady -1) {
				dangerAhead = true;
			}
			if (snakeTailx[i] == headx+1 && snakeTaily[i] == heady) {
				dangerRight = true;
			}
			if (snakeTailx[i] == headx-1 && snakeTaily[i] == heady) {
				dangerLeft = true;
			}
		}
		if (headx-1 == -1) {
			dangerLeft = true;
		}
		if (headx+1 == width) {
			dangerRight = true;
		}
		if (heady-1 == -1) {
			dangerAhead = true;
		}
		break;	//problem going right and left with turning right
	case Down:
		for (int i = 0; i < snakeTailLength; i++) {
			if (snakeTailx[i] == headx-1 && snakeTaily[i] == heady) {
				dangerRight = true;
			}
			if (snakeTailx[i] == headx+1 && snakeTaily[i] == heady) {
				dangerLeft = true;
			}
			if (snakeTailx[i] == headx && snakeTaily[i] == heady + 1) {
				dangerAhead = true;
			}
		}
		if (headx-1 == -1) {
			dangerRight = true;
		}
		if (headx+1 == width) {
			dangerLeft = true;
		}
		if (heady+1 == height) {
			dangerAhead = true;
		}
		break;
	}
};

void Game::resetvars() {
	if (gameUpdated == true) {
		dangerRight = false;	
		dangerLeft = false;
		dangerAhead = false;
	}
}

void Game::AImoveSnake() {	//need to check for danger ahead still, do that first in this function
	switch (sDir) {
	case Left:{
		if (appleLeft) {
			if (dangerLeft) {
				;
			}
			else {
				sDir = Down;
			}
		}
		else if (appleRight) {
			if (dangerRight) {
				;
			}
			else {
				sDir = Up;
			}
		}
		else if (!appleRight && !appleLeft && !appleAhead) {
			if (dangerRight) {
				;
			}
			else if(dangerLeft){
				;
			}
			else {
				sDir = Up;
			}
		}
		if (dangerAhead) {
			if (dangerLeft) {
				sDir = Up;
			}
			else if (dangerRight) {
				sDir = Down;
			}
		}
		break;
	}
	case Right: {
		if (appleLeft) {
			if (dangerLeft) {
				;
			}
			else {
				sDir = Up;
			}
		}
		else if (appleRight) {
			if (dangerRight) {
				;
			}
			else {
				sDir = Down;
			}
		}
		else if (!appleRight && !appleLeft && !appleAhead) {
			if (dangerRight) {
				;
			}
			else if (dangerLeft) {
				;
			}
			else {
				sDir = Down;
			}
		}
		if (dangerAhead) {
			if (dangerLeft) {
				sDir = Down;
			}
			else if (dangerRight) {
				sDir = Up;
			}
		}
		break;
	}
	case Up: {
		if (appleLeft) {
			if (dangerLeft) {
				;
			}
			else {
				sDir = Left;
			}
		}
		else if (appleRight) {
			if (dangerRight) {
				;
			}
			else {
				sDir = Right;
			}
		}
		else if (!appleRight && !appleLeft && !appleAhead) {
			if (dangerRight) {
				;
			}
			else if (dangerLeft) {
				;
			}
			else {
				sDir = Right;
			}
		}
		if (dangerAhead) {
			if (dangerLeft) {
				sDir = Right;
			}
			else if (dangerRight) {
				sDir = Left;
			}
		}
		break;
	}
	case Down: {
		if (appleLeft) {
			if (dangerLeft) {
				;
			}
			else {
				sDir = Right;
			}
		}
		else if (appleRight) {
			if (dangerRight) {
				;
			}
			else {
				sDir = Left;
			}
		}
		else if (!appleRight && !appleLeft && !appleAhead) {
			if (dangerRight) {
				;
			}
			else if (dangerLeft) {
				;
			}
			else {
				sDir = Left;
			}
		}
		if (dangerAhead) {
			if (dangerLeft) {
				sDir = Left;
			}
			else if (dangerRight) {
				sDir = Right;
			}
		}
		break;
	}
	}
};