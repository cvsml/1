#include "StdAfx.h"
#include "GestureGenerator.h"
#include <ctime>
#include <cstdlib>

GestureGenerator::GestureGenerator()
{
	srand(time(0));
}

GestureGenerator::~GestureGenerator()
{

}

Gesture GestureGenerator::nextGesture()
{
	int gesture = rand() % 4; // Random number from 0 to 3
	Gesture result = Gesture::Gestures[GESTURE_CENTER];

	switch(gesture)
	{
		case 0:
			result = Gesture::Gestures[GESTURE_LEFT];
		break;

		case 1:
			result = Gesture::Gestures[GESTURE_RIGHT];
		break;

		case 2:
			result = Gesture::Gestures[GESTURE_LEFT_EYE];
		break;

		case 3:
			result = Gesture::Gestures[GESTURE_RIGHT_EYE];
		break;

		default:
			printf("%s", "Bug in GestureGenerator::nextGesture, invalid number generated\n");
		break;
	}

	return result;
}
