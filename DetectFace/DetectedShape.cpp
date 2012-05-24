#include "StdAfx.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace std;
using namespace cv;

#include "DetectedShape.h"

DetectedShape::DetectedShape(Rect rect)
{
	this->rect = rect;
	center = Vec2f(rect.x + rect.width/2.0f,rect.y + rect.height/2.0f);
}

Rect DetectedShape::getRect()
{
	return rect;
}

Vec2f DetectedShape::getCenter()
{
	return center;
}