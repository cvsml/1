#ifndef GAME_H
#define GAME_H

#include "cv.h"
#include "highgui.h"
#include <opencv2/gpu/gpu.hpp>

#include "GestureGenerator.h"
#include "GestureSequence.h"
#include "FPSCalculator.h"
#include "Face.h"
#include "Gesture.h"
#include "ObjectDetector.h"
#include "GestureDetector.h"

#include <string>
using namespace std;

class Game {
private:
	const static unsigned int victorySequenceLength;

	GestureSequence sequence;
	unsigned int index;

	GestureGenerator generator;

	GESTURE previousGesture;

	Face faceContainer;
	GestureDetector gesture;
	FPSCalculator fps;
	ObjectDetector faceDetector;
	ObjectDetector leftEyeDetector;
	ObjectDetector rightEyeDetector;
	ObjectDetector noseDetector;

	bool newTurnFlag;
	void newTurn();
	bool checkVictory();

public:
	Game();
	~Game();

	void newGame();
	void handleGesture(GESTURE newGesture);

	void update(IplImage *img);
	void draw(IplImage *img);
	std::string getFPS();

	bool isNewTurn();
	GestureSequence getSequence();
};

#endif

