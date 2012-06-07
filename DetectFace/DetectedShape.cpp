#include "StdAfx.h"
#include <ctime>
#include "DetectedShape.h"

const double DetectedShape::oldTime = 0.5;

DetectedShape::DetectedShape(Rect rect)
{
	setRect(rect);
}

DetectedShape::DetectedShape()
{
	rect.x = 0;
	rect.y = 0;
	rect.width = 0;
	rect.height = 0;
	center = Vec2f(0, 0);
	valid = false;
	timeStamp = -1;
}

DetectedShape::~DetectedShape()
{

}

Rect DetectedShape::getRect()
{
	return rect;
}

void DetectedShape::setRect(const Rect &rect)
{
	valid = rect.size().area() != 0;

	if(valid)
	{
		this->rect = rect;	
		center = Vec2f(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
		timeStamp = time(NULL);
	}
}

Vec2f DetectedShape::getCenter()
{
	return center;
}

void DetectedShape::draw(IplImage *img, CvScalar color)
{
	if(isValid())
		cvRectangle(img, rect.tl(), rect.br(), color, 3);
}

bool DetectedShape::isValid()
{
	// If you're valid you're valid. If not, then you're valid if less than OLD_TIME has past since you were last valid
	return (valid || (!valid && (difftime(time(NULL), timeStamp) < DetectedShape::oldTime)));
}