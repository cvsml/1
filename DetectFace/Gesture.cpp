#include "stdafx.h"
#include "Gesture.h"
#include <iostream>

Gesture Gesture::Gestures[] = {
	Gesture(GESTURE_LEFT, "Looking Left", "LLeft.bmp"), 
	Gesture(GESTURE_CENTER, "Looking Center", "Center.bmp"), 
	Gesture(GESTURE_RIGHT, "Looking Right", "LReft.bmp"), 
	Gesture(GESTURE_LEFT_EYE, "Hiding Left", "HLeft.bmp"),
	Gesture(GESTURE_RIGHT_EYE, "Hiding Right", "HRight.bmp")};

Gesture::Gesture()
{
	type = GESTURE_CENTER;
}

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

std::string Gesture::getName()
{
	return name;
}

void  Gesture::draw()
{
	//Throw UnimplamentedException()
}

bool Gesture::operator== (const Gesture &other)
{
	return this->type == other.type;
}

bool Gesture::operator!= (const Gesture &other)
{
	return !(*this == other);
}