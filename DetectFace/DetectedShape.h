#ifndef DETECTED_SHAPE_H
#define DETECTED_SHAPE_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class DetectedShape {
private:
	Rect rect;
	Vec2f center;
	bool valid;

public:
	DetectedShape(Rect);
	DetectedShape();
	~DetectedShape();

	Rect getRect();
	void setRect(const Rect &rect);
	Vec2f getCenter();
	void draw(IplImage *img, CvScalar color);
	bool isValid();
};

#endif
