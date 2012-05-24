#ifndef DETECTED_SHAPE_H
#define DETECTED_SHAPE_H




class DetectedShape {
private:
	Rect rect;
	Vec2f center;

public:
	DetectedShape(Rect);
	~DetectedShape();

	Rect getRect();
	Vec2f getCenter();
};

#endif
