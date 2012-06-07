#ifndef GESTURE_GENERATOR_H
#define GESTURE_GENERATOR_H

#include "Gestures.h"

class GestureGenerator {
public:
	GestureGenerator();
	~GestureGenerator();

	GESTURE nextGesture();
};

#endif