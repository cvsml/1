#ifndef DETECTED_SHAPE_H
#define DETECTED_SHAPE_H


class DetectedShape {
private:
	Rect rect;

public:
	DetectedShape(Rect);
	~DetectedShape();

	std::vector<Rect> detect(Mat&);
	std::vector<Rect> detect(Mat&, Rect&);

	Rect detectLikely(Mat&);
	Rect detectLikely(Mat&, Rect&);

	static Rect getLargest(std::vector<Rect>&);
};

#endif
