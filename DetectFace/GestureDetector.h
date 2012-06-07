#ifndef GESTURE_DETECTOR_H
#define GESTURE_DETECTOR_H

#include "Gestures.h"

class GestureDetector {
	const static double LEFT_CHECKPOINT;
	const static double CENTER_LEFT;
	const static double CENTER_CHECKPOINT;
	const static double CENTER_RIGHT;
	const static double RIGHT_CHECKPOINT;

	DIRECTION direction;
	GESTURE gesture;
	bool changedGesture;

	GESTURE directionToGesture(DIRECTION direction);
	DIRECTION getDirection(double ratio);

public:
	GestureDetector();
	~GestureDetector();

	GESTURE updateGesture (double ratio, bool leftEyeValidity, bool rightEyeValdity, bool noseValidity);
	GESTURE getGesture();
	void print(GESTURE gesture);
	void print();
	bool newGesture();
};

#endif

