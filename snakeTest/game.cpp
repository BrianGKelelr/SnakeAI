#include "game.hpp"

void Game::gameStart() {	//used to start game
	isGameOver = false;
	sDir = STOP;			//stops player movement
	headx = width / 2;		//puts snake in middle of game board
	heady = height / 2;
	fruitx = rand() % width;	//randomly places fruit
	fruity = rand() % height;
	score = 0;		//resets score
};

std::string Game::boardRender() {
	system("cls");	//clears the console
	std::string output;

	for (int i = 0; i < width + 2; i++) {	//sets up top wall using "-" character
		cout << "-";
	}
	cout<< "\n";

	for (int i = 0; i < height; i++) {		//goes through game board one row at a time to print everything
		for (int j = 0; j <= width; j++) {	//sets up side walls with "|" character
			if (j == 0 || j == width) {
				cout<< "|";
			}

			if (i == heady && j == headx) {		//if current printing coordinate equals coordinates of snake head, print snake head
				cout<< "O";
			}
			else if (i == fruity && j == fruitx) {	//prints fruit (money) if coordinates equal coordinates of fruit
				cout<< "$";
			}
			else {	//snake body
				bool prTail = false;
				for (int k = 0; k < snakeTailLength; k++) {
					if (snakeTailx[k] == j && snakeTaily[k] == i) {
						cout<< "o";
						prTail = true;	//sets prTail to true to avoid infinite loop
					}
				}
				if (!prTail) {		//prints empty space if not a wall, fruit, or snake
					cout<< " ";
				}
			}
			cout<< "\n";
		}
	}
	for (int i = 0; i < width + 2; i++) {	//sets up bottom wall using "-" character
		cout<< "-";
	}
	cout<< "\n";

	cout<< + "Score: " + to_string(score) + "/n";	//prints score

	return output;	//returns what everything should look like
};

void Game::updateGame() {
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
		snakeTailLength++;
	}
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
		case 'S':
			sDir = Down;
			break;
		case 'x':				//if x is pressed, ends game
			isGameOver = true;
			break;
		}
	}
};