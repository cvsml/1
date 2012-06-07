#ifndef GAME_H
#define GAME_H

#include "GestureGenerator.h"
#include "GestureSequence.h"

class Game {
private:
	GestureSequence sequence;

public:
	Game();
	~Game();

	void newGame();
	void newTurn();
};

#endif

