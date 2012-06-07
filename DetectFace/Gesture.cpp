#include "stdafx.h"
#include "Gesture.h"
#include <iostream>

Gesture Gesture::Gestures[] = {Gesture(GESTURE_LEFT, "Looking Left", "LLeft.bmp"), 
	Gesture(GESTURE_LEFT, "Looking Center", "Center.bmp"), 
	Gesture(GESTURE_LEFT, "Looking Right", "LReft.bmp"), 
	Gesture(GESTURE_LEFT, "Hidding Left", "HLeft.bmp"),
	Gesture(GESTURE_LEFT, "Hidding Right", "HRight.bmp")};

Gesture::Gesture(GESTURE type, string name, string imagePath)
{
	this->type = type;
	this->name = name;
	this->imagePath = imagePath;
}

Gesture::~Gesture()
{
}

GESTURE Gesture::getValue()
{
	return type;
}

void Gesture::print()
{
	cout << name;
}

void  Gesture::draw()
{
	//Throw UnimplamentedException()
}

bool Gesture::operator== (const Gesture &other)
{
	return !(this->type == other.type);
}

bool Gesture::operator!= (const Gesture &other)
{
	return !(this->type != other.type);
}