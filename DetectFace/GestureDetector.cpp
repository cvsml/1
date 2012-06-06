#include "StdAfx.h"
#include "GestureDetector.h"

const double GestureDetector::LEFT_CHECKPOINT = 0.35;
const double GestureDetector::CENTER_LEFT = 0.45;
const double GestureDetector::CENTER_CHECKPOINT = 0.5;
const double GestureDetector::CENTER_RIGHT = 0.55;
const double GestureDetector::RIGHT_CHECKPOINT = 0.65;

GestureDetector::GestureDetector()
{
	direction = DIRECTION_CENTER;
	gesture = GESTURE_CENTER;
}


GestureDetector::~GestureDetector()
{

}

GESTURE GestureDetector::getGesture()
{
	return gesture;
}

/*
 * Left		| Buffer	  | Center		| Buffer	  | Right
 * 0 - 0.35 | 0.35 - 0.45 | 0.45 - 0.55 | 0.55 - 0.65 | 0.65 - 1.0
 */
GESTURE GestureDetector::updateGesture (double ratio, bool leftEyeValidity, bool rightEyeValidity)
{
	if(leftEyeValidity && rightEyeValidity)
	{
		if (ratio > RIGHT_CHECKPOINT)
			direction = DIRECTION_RIGHT;
		else if (ratio  < LEFT_CHECKPOINT)
			direction = DIRECTION_LEFT;
		else 
		{
			if (ratio < CENTER_RIGHT && direction == DIRECTION_RIGHT)
				direction = DIRECTION_CENTER;
			else if(ratio > CENTER_LEFT && direction == DIRECTION_LEFT)
				direction = DIRECTION_CENTER;
		}
	}

	if(direction == DIRECTION_CENTER)
	{
		if(!leftEyeValidity)
			gesture = GESTURE_LEFT_EYE;
		else if(!rightEyeValidity)
			gesture = GESTURE_RIGHT_EYE;
		else
			gesture = GESTURE_CENTER;
	}
	else
	{
		gesture = directionToGesture(direction);
	}

	return gesture;
}

void GestureDetector::print(GESTURE gesture)
{
	switch(gesture) {
		case GESTURE_LEFT:
			printf("Looking left\n");
		break;

		case GESTURE_CENTER:
			printf("Looking center\n");
		break;

		case GESTURE_RIGHT:
			printf("Looking right\n");
		break;

		case GESTURE_LEFT_EYE:
			printf("Shut left eye\n");
		break;

		case GESTURE_RIGHT_EYE:
			printf("Shut right eye\n");
		break;

		default:
			printf("???\n");
		break;
	}
}

void GestureDetector::print()
{
	print(gesture);
}

GESTURE GestureDetector::directionToGesture(DIRECTION direction)
{
	switch(direction) {
		case DIRECTION_LEFT:
			return GESTURE_LEFT;
		break;

		case DIRECTION_CENTER:
			return GESTURE_CENTER;
		break;

		case DIRECTION_RIGHT:
			return GESTURE_RIGHT;
		break;

		default:
			printf("Error in GestureDetector::directionToGesture. Invalid direction.\n");
			return GESTURE_CENTER;
		break;
	}
}