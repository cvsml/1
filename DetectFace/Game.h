#ifndef GAME_H
#define GAME_H

#include "GestureGenerator.h"
#include "GestureSequence.h"

class Game {
private:
	const static unsigned int victorySequenceLength;

	GestureSequence sequence;
	unsigned int index;

	GestureGenerator generator;

	GESTURE previousGesture;

	void newTurn();
	bool checkVictory();

public:
	Game();
	~Game();

	void newGame();
	void handleGesture(GESTURE newGesture);
};

#endif

