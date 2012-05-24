#include "StdAfx.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

#include "ObjectDetector.h";

ObjectDetector::ObjectDetector(String xmlPath, double scaleFactor = 1.1, int numNeigbors = 3, int flags = CV_HAAR_SCALE_IMAGE, Size minSize = Size(30,30), Size maxSize = Size())
{
	this->scaleFactor = scaleFactor;
	this->numNeighbors = numNeigbors;
	this->flags = flags;
	this->minSize = minSize;
	this->maxSize = maxSize;
	isValid = cascade.load(xmlPath);
}

std::vector<Rect> ObjectDetector::detect(Mat& image)
{
	std::vector<Rect> found = std::vector<Rect>();
	if(!isValid)
		return found;

	cascade.detectMultiScale( image, found, scaleFactor, numNeighbors, flags, minSize, maxSize );
	return found;
}

std::vector<Rect> ObjectDetector::detect(Mat& image, Rect& ROI)
{
	Mat roiImg = Mat(image, ROI);
	return detect(roiImg);
}

Rect ObjectDetector::detectLikely(Mat& image)
{
	std::vector<Rect> rectangles = detect(image);
	return getLargest(rectangles);
}

Rect ObjectDetector::detectLikely(Mat& image, Rect& ROI)
{
	Mat roiImg = Mat(image, ROI);
	return detectLikely(roiImg);
}

Rect ObjectDetector::getLargest(std::vector<Rect>& rectangles)
{
	Rect max = Rect(0,0,0,0);
	for(int i =0; i < rectangles.size(); i++)
	{
		if(rectangles[i].size().area() >= max.size().area())
			max = rectangles[i];
	}
	return max;
}