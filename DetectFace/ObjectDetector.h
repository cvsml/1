#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H


class ObjectDetector {
private:
	CascadeClassifier cascade;
	double scaleFactor;
	int numNeighbors;
	int flags;
	bool valid;
	CvSize minSize;
	CvSize maxSize;

	Rect getLargest(std::vector<Rect>&);

public:
	ObjectDetector(string xmlPath, double scaleFactor = 1.1, int numNeigbors = 3, int flags = CV_HAAR_SCALE_IMAGE, Size minSize = Size(30, 30), Size maxSize = Size());
	~ObjectDetector();

	std::vector<Rect> detect(Mat&);
	std::vector<Rect> detect(Mat&, Rect&);

	Rect detectLikely(Mat&);
	Rect detectLikely(Mat&, Rect&);

	bool isValid();
};

#endif
