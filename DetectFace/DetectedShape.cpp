#include "StdAfx.h"
#include "DetectedShape.h"

DetectedShape::DetectedShape(Rect rect)
{
	this->rect = rect;
	center = Vec2f(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
	valid = rect.size().area() != 0;
}

DetectedShape::~DetectedShape()
{

}

Rect DetectedShape::getRect()
{
	return rect;
}

Vec2f DetectedShape::getCenter()
{
	return center;
}

void DetectedShape::draw(IplImage *img, CvScalar color)
{
	if(valid)
		cvRectangle(img, rect.tl(), rect.br(), color, 3);
}

bool DetectedShape::isValid()
{
	return valid;
}