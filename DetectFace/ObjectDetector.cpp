#include "StdAfx.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

#include "ObjectDetector.h"

ObjectDetector::ObjectDetector(String xmlPath, double scaleFactor, int numNeigbors, int flags, Size minSize, Size maxSize)
{
	this->scaleFactor = scaleFactor;
	this->numNeighbors = numNeigbors;
	this->flags = flags;
	this->minSize = minSize;
	this->maxSize = maxSize;
	valid = cascade.load(xmlPath);
}

ObjectDetector::~ObjectDetector()
{

}

std::vector<Rect> ObjectDetector::detect(Mat& image)
{
	vector<Rect> found;

	if(!valid)
		return found;

	cascade.detectMultiScale(image, found, scaleFactor, numNeighbors, flags, minSize, maxSize);
	return found;
}

std::vector<Rect> ObjectDetector::detect(Mat &image, Rect &ROI)
{
	Mat roiImg = Mat(image, ROI);
	std::vector<Rect> result = detect(roiImg);

	// Covnert the result vector from relative to absolute coordinates
	for(unsigned int i = 0; i < result.size(); ++i) { 
		result[i].x += ROI.x;
		result[i].y += ROI.y;
	}

	return result;
}

Rect ObjectDetector::detectLikely(Mat &image)
{
	std::vector<Rect> rectangles = detect(image);
	return getLargest(rectangles);
}

Rect ObjectDetector::detectLikely(Mat &image, Rect &ROI)
{
	if(ROI.width == 0 || ROI.height == 0)
		return detectLikely(image);

	Mat roiImg = image(ROI);

	Rect relative = detectLikely(roiImg);
	return Rect(relative.x + ROI.x, relative.y + ROI.y, relative.width, relative.height);
}

Rect ObjectDetector::getLargest(std::vector<Rect> &rectangles)
{
	Rect max = Rect(0, 0, 0, 0);

	for(unsigned int i = 0; i < rectangles.size(); i++)
	{
		if(rectangles[i].size().area() >= max.size().area())
			max = rectangles[i];
	}

	return max;
}

bool ObjectDetector::isValid()
{
	return valid;
}