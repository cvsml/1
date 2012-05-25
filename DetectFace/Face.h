#ifndef FACE_H
#define FACE_H

class Face {
private:
	std::shared_ptr<DetectedShape> faceArea;
	std::shared_ptr<DetectedShape> noseArea;
	std::shared_ptr<DetectedShape> leftEyeArea;
	std::shared_ptr<DetectedShape> rightEyeArea;

	double getDegree(Vec2f&, Vec2f&);
	double getDegree(Vec2f&, Vec2f&, Vec2f&);

public:
	Face();
	~Face();

	std::shared_ptr<DetectedShape> getFaceArea();
	std::shared_ptr<DetectedShape> getNoseArea();
	std::shared_ptr<DetectedShape> getLeftEyeArea();
	std::shared_ptr<DetectedShape> getRightEyeArea();

	double getLeftAngle();
	double getRightAngle();
};

#endif
