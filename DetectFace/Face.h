#ifndef FACE_H
#define FACE_H



class Face {
private:
	DetectedShape* faceArea;
	DetectedShape* noseArea;
	DetectedShape* leftEyeArea;
	DetectedShape* rightEyeArea;

	double getDegree(Vec2f&, Vec2f&);
	double getDegree(Vec2f&, Vec2f&, Vec2f&);

public:
	Face(DetectedShape*, DetectedShape*, DetectedShape*, DetectedShape*);
	~Face();

	void setFaceArea(DetectedShape*);
	void setNoseArea(DetectedShape*);
	void setLeftEyeArea(DetectedShape*);
	void setRightArea(DetectedShape*);

	double getLeftAngle();
	double getRightAngle();
};

#endif
