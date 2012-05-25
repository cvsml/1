#include "StdAfx.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace cv;

#include "DetectedShape.h"
#include "Face.h"

Face::Face()
{
	faceArea = shared_ptr<DetectedShape>(new DetectedShape());
	noseArea = shared_ptr<DetectedShape>(new DetectedShape());
	leftEyeArea = shared_ptr<DetectedShape>(new DetectedShape());
	rightEyeArea = shared_ptr<DetectedShape>(new DetectedShape());
}

Face::~Face()
{

}

std::shared_ptr<DetectedShape> Face::getFaceArea()
{
	return faceArea;
}

std::shared_ptr<DetectedShape> Face::getNoseArea()
{
	return noseArea;
}

std::shared_ptr<DetectedShape> Face::getLeftEyeArea()
{
	return leftEyeArea;
}

std::shared_ptr<DetectedShape> Face::getRightEyeArea()
{
	return rightEyeArea;
}

double Face::getLeftAngle()
{
	return getDegree(rightEyeArea->getCenter(), leftEyeArea->getCenter(), noseArea->getCenter());
}

double Face::getRightAngle()
{
	return getDegree(leftEyeArea->getCenter(), rightEyeArea->getCenter(), noseArea->getCenter());
}

double Face::getDegree(Vec2f &vec1, Vec2f &vec2)
{
	if(norm(vec1) == 0.0)
	{
		//cout << "Attempted to divide vec1 by zero in getDegree";
		return 0;
	}

	normalize(vec1, vec1);

	if(norm(vec2) == 0.0)
	{
		//cout << "Attempted to divide vec2 by zero in getDegree";
		return 0;
	}

	normalize(vec2, vec2);

	return acos(vec1.dot(vec2)) * 180.0 / M_PI;
}

double Face::getDegree(Vec2f &center1, Vec2f &center2, Vec2f &center3)
{
	Vec2f vec1 = center2 - center1;
	Vec2f vec2 = center3 - center1;

	return getDegree(vec1, vec2);
}