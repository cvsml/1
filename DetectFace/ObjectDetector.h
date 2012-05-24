#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H


class ObjectDetector {
private:
	CascadeClassifier cascade;
	double scaleFactor;
	int numNeighbors;
	int flags;
	bool isValid;
	CvSize minSize;
	CvSize maxSize;

public:
	ObjectDetector(String, double, int, int, Size, Size);
	~ObjectDetector();

	std::vector<Rect> detect(Mat&);
	std::vector<Rect> detect(Mat&, Rect&);

	Rect detectLikely(Mat&);
	Rect detectLikely(Mat&, Rect&);

	static Rect getLargest(std::vector<Rect>&);
};

#endif
