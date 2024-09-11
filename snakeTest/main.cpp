#include "game.hpp"

int main() {
	Game snake;

	snake.gameStart();
	while (!snake.isGameOver) {
		std::cout << snake.boardRender();
		snake.input();
		snake.updateGame();
		Sleep(100);		//delay, set higher for less delay and lower for more delay
	}
	return 0;
}