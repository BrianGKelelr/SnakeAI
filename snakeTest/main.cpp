#include "game.hpp"

  int main() {
	Game snake;

	snake.gameStart();
	while (!snake.isGameOver) {
		std::cout << snake.boardRender();
		snake.input();
		snake.updateGame();
		snake.getApplePos();
		snake.resetvars();
		Sleep(5);		//delay, set higher for more delay
	}
	return 0;
}