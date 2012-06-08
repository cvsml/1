#include "StdAfx.h"
#include "Game.h"
#include <iostream>

const unsigned int Game::victorySequenceLength = 4;

Game::Game()
{
	previousGesture = GESTURE_CENTER;
}

Game::~Game()
{

}

void Game::newGame()
{
	cout << "NEW GAME" << endl;
	sequence.reset();
	newTurn();
}

bool Game::checkVictory()
{
	if(sequence.size() == victorySequenceLength)
	{
		cout << "YOU WON! Yay!!" << endl << "--------------" <<  endl;
		newGame();
		return true;
	}

	return false;
}

void Game::newTurn()
{
	if(checkVictory())
		return;
	
	sequence.push(generator.nextGesture());
	sequence.print();
	index = 0;
}

void Game::handleGesture(GESTURE newGesture)
{
	// If I got center, then the previous is center
	if(newGesture == GESTURE_CENTER)
	{
		previousGesture = GESTURE_CENTER;
		return;
	}

	// I didn't get center, and the previous gesture is not center, ignore it
	if(previousGesture != GESTURE_CENTER)
	{
		return;
	}

	// Now we didn't get center, and the previous IS center
	if(newGesture == sequence[index])
	{
		index++;
		cout << "Ding!" << endl;

		if(index == sequence.size())
			newTurn();
	}

	else
	{
		cout << "EPIC FAIL!" << endl;
		newGame();
	}
}