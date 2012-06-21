#ifndef FACE_H
#define FACE_H

using namespace std;

#include "DetectedShape.h"

class Face {
private:
	shared_ptr<DetectedShape> faceArea;
	shared_ptr<DetectedShape> noseArea;
	shared_ptr<DetectedShape> leftEyeArea;
	shared_ptr<DetectedShape> rightEyeArea;
	
	//double getDegree(Vec2f&, Vec2f&);
	//double getDegree(Vec2f&, Vec2f&, Vec2f&);

public:
	Face();
	~Face();

	shared_ptr<DetectedShape> getFaceArea();
	shared_ptr<DetectedShape> getNoseArea();
	shared_ptr<DetectedShape> getLeftEyeArea();
	shared_ptr<DetectedShape> getRightEyeArea();

	/*
	double getLeftAngle();
	double getRightAngle();
	*/
	double getRatio();
	//double getRatioOld();
	bool isLeftEyeValid();
	bool isRightEyeValid();
	bool isNoseValid();
};

#endif
