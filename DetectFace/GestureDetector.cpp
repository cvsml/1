#include "StdAfx.h"
#include "GestureDetector.h"

const double GestureDetector::LEFT_CHECKPOINT = 0.35;
const double GestureDetector::CENTER_LEFT = 0.45;
const double GestureDetector::CENTER_CHECKPOINT = 0.5;
const double GestureDetector::CENTER_RIGHT = 0.55;
const double GestureDetector::RIGHT_CHECKPOINT = 0.65;

GestureDetector::GestureDetector()
{
	mode = MODE_CENTER;
}


GestureDetector::~GestureDetector()
{

}

MODES GestureDetector::getMode()
{
	return mode;
}

/*
 * Left		| Buffer	  | Center		| Buffer	  | Right
 * 0 - 0.35 | 0.35 - 0.45 | 0.45 - 0.55 | 0.55 - 0.65 | 0.65 - 1.0
 */
MODES GestureDetector::updateMode (double ratio)
{
	if (ratio > RIGHT_CHECKPOINT)
		mode = MODE_RIGHT;
	else if (ratio  < LEFT_CHECKPOINT)
		mode = MODE_LEFT;
	else {
		if (ratio < CENTER_RIGHT && mode == MODE_RIGHT)
			mode = MODE_CENTER;
		else if(ratio > CENTER_LEFT && mode == MODE_LEFT)
			mode = MODE_CENTER;
	}

	return mode;
}

void GestureDetector::printMode(MODES mode)
{
	switch(mode) {
		case MODE_LEFT:
			printf("Looking left\n");
		break;

		case MODE_CENTER:
			printf("Looing center\n");
		break;

		case MODE_RIGHT:
			printf("Looking right\n");
		break;

		default:
			printf("???\n");
		break;
	}
}

void GestureDetector::printMode()
{
	printMode(mode);
}