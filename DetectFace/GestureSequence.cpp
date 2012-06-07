#include "StdAfx.h"
#include "GestureSequence.h"

const unsigned int GestureSequence::sequenceLength = 20;

GestureSequence::GestureSequence()
{

}

GestureSequence::~GestureSequence()
{

}

void GestureSequence::push(GESTURE gesture)
{
	gestureSequence.push_back(gesture);
}

GESTURE GestureSequence::peek(GESTURE gesture)
{
	if(gestureSequence.empty())
	{
		printf("%s\n", "Error in GestureSequence::peek, attempted to peek in empty sequence"); 
		return GESTURE_CENTER;
	}

	return gestureSequence.back();
}

bool GestureSequence::operator = (const GestureSequence &other)
{
	if(gestureSequence.size() != other.gestureSequence.size())
		return false;

	for(int i = 0; i < gestureSequence.size(); ++i)
	{
		if(gestureSequence[i] != other.gestureSequence[i])
			return false;
	}

	return true;
}
