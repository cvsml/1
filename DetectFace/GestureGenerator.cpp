#include "StdAfx.h"
#include "GestureGenerator.h"
#include <ctime>
#include <cstdlib>

GestureGenerator::GestureGenerator()
{
	srand((unsigned int)time(NULL));
}

GestureGenerator::~GestureGenerator()
{

}

GESTURE GestureGenerator::nextGesture()
{
	int gesture = rand() % 4; // Random number from 0 to 3
	GESTURE result = GESTURE_CENTER;

	switch(gesture)
	{
		case 0:
			result = GESTURE_LEFT;
		break;

		case 1:
			result = GESTURE_RIGHT;
		break;

		case 2:
			result = GESTURE_LEFT_EYE;
		break;

		case 3:
			result = GESTURE_RIGHT_EYE;
		break;

		default:
			printf("%s", "Bug in GestureGenerator::nextGesture, invalid number generated\n");
		break;
	}

	return result;
}
