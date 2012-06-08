#include "StdAfx.h"
#include "GestureSequence.h"
#include <iostream>

void GestureSequence::reset()
{
	gestureSequence.clear();
}

GestureSequence::GestureSequence()
{
	reset();
}

GestureSequence::~GestureSequence()
{

}

void GestureSequence::push(GESTURE gesture)
{
	gestureSequence.push_back(gesture);
}

GESTURE GestureSequence::peek()
{
	if(gestureSequence.empty())
	{
		printf("%s\n", "Error in GestureSequence::peek, attempted to peek in empty sequence"); 
		return GESTURE_CENTER;
	}

	return gestureSequence.back();
}

GESTURE GestureSequence::operator [](int i)
{
	if(i < 0 || i >= (int)gestureSequence.size())
	{
		cout << "Error in GestureSequence::operator [], invalid index" << endl;
		return GESTURE_CENTER;
	}

	return gestureSequence[i];
}

int GestureSequence::size()
{
	return gestureSequence.size();
}

bool GestureSequence::operator == (const GestureSequence &other)
{
	if(gestureSequence.size() != other.gestureSequence.size())
		return false;

	for(unsigned int i = 0; i < (int)gestureSequence.size(); ++i)
	{
		if(gestureSequence[i] != other.gestureSequence[i])
			return false;
	}

	return true;
}

void GestureSequence::print()
{
	cout << "----------------------------" << endl;

	for(unsigned int i = 0; i < gestureSequence.size(); ++i)
	{
		printf("%d ", i);
		Gesture::Gestures[gestureSequence[i]].print();
		cout << endl;
	}
}
