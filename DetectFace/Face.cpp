#include "StdAfx.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>

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

shared_ptr<DetectedShape> Face::getFaceArea()
{
	return faceArea;
}

shared_ptr<DetectedShape> Face::getNoseArea()
{
	return noseArea;
}

shared_ptr<DetectedShape> Face::getLeftEyeArea()
{
	return leftEyeArea;
}

shared_ptr<DetectedShape> Face::getRightEyeArea()
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

/*
 * Nose is between the left and the right eye, between 0 and 1. If the ratio is 0.3, then that means
 * that the nose is 30% between the left and the right eye, closer to the left eye.
 */
double Face::getRatioOld()
{
	double xLeftEye = leftEyeArea->getCenter()[0];
	double xRightEye = rightEyeArea->getCenter()[0];
	double xNose = noseArea->getCenter()[0];

	return (xNose - xLeftEye) / (xRightEye - xLeftEye);
}

double Face::getRatio()
{
	Vec2f leftEye = leftEyeArea->getCenter();
	Vec2f rightEye = rightEyeArea->getCenter();
	Vec2f nose = noseArea->getCenter();
	Vec2f n = rightEye - leftEye;
	normalize(n, n);

	// We projected the vector (Nose - leftEye) onto (rightEye - leftEye)
	// then divided the norm of that vector by the norm of (rightEye - leftEye)
	return norm((leftEye - nose).dot(n) * n) / norm(rightEye - leftEye);
}