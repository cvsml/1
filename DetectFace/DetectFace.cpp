// OpenCV Sample Application: facedetect.c
#include "stdafx.h"

#define _USE_MATH_DEFINES

// Include header files
#include "cv.h"
#include "highgui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
#include <iostream>
#include <cmath>

#include "FPSCalculator.h"
#include "DetectedShape.h"
#include "ObjectDetector.h"

using namespace std;
using namespace cv;

// Function prototype for detecting and drawing an object from an image
void detect_and_draw(IplImage *image);
void drawFaces(CvSeq *faces, IplImage *img, CvScalar color);

FPSCalculator fps;

ObjectDetector faceDetector("haarcascade_frontalface_alt2.xml", 1.3f);
ObjectDetector leftEyeDetector("haarcascade_mcs_lefteye.xml", 1.3f);
ObjectDetector rightEyeDetector("haarcascade_mcs_righteye.xml", 1.3f);
ObjectDetector noseDetector("haarcascade_mcs_nose.xml", 1.3f);

// Main function, defines the entry point for the program.
int main(int argc, char** argv)
{
    // Structure for getting video from camera or avi
    CvCapture* capture = 0;

    // Images to capture the frame from video or camera or from file
    IplImage *frame, *frame_copy = 0, *frame_copy_bw = 0;

    // Check whether the cascade has loaded successfully. Else report and error and quit
	if(!faceDetector.isValid() || !leftEyeDetector.isValid() || !rightEyeDetector.isValid() || !noseDetector.isValid())
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade(s)\n" );
		getchar();
        return -1;
    }
    
    capture = cvCaptureFromCAM(0);

    // Create a new named window with title: result
    cvNamedWindow("Simon", 1);

    // Find if the capture is loaded successfully or not.
    // If loaded succesfully, then:
    if(capture)
    {
        // Capture from the camera.
        for(;;)
        {		
            // Capture the frame and load it in IplImage
            if(!cvGrabFrame(capture))
                break;
			
            frame = cvRetrieveFrame(capture);

            // If the frame does not exist, quit the loop
            if(!frame)
                break;
            
            // Allocate framecopy as the same size of the frame
			float scale = 1.0f;
            if(!frame_copy) {
                //frame_copy = cvCreateImage( cvSize(frame->width,frame->height), IPL_DEPTH_8U, frame->nChannels );
				frame_copy = cvCreateImage(cvSize(frame->width*scale, frame->height*scale), IPL_DEPTH_8U, frame->nChannels);
				frame_copy_bw = cvCreateImage(cvSize(frame->width*scale, frame->height*scale), IPL_DEPTH_8U, 1);
				//cvCvtColor(frame, frame_copy, CV_BGR2GRAY);
			}
			
            // Check the origin of image. If top left, copy the image frame to frame_copy. 
            //if( frame->origin == IPL_ORIGIN_TL )
            //    cvCopy( frame, frame_copy, 0 );
            // Else flip and copy the image
           // else
            //    cvFlip( frame, frame_copy, 0 );

			//cvCvtColor(frame, frame_copy, CV_BGR2GRAY);
			cvResize(frame, frame_copy, scale);
			//cvCvtColor(frame_copy, frame_copy_bw, CV_BGR2GRAY);
			detect_and_draw(frame_copy);

            // Wait for a while before proceeding to the next frame
            if(cvWaitKey(1) >= 0 )
                break;
			
			fps.addFrame();
			printf("FPS: %d\n", fps.getFPS());
        }

        // Release the images, and capture memory
        cvReleaseImage( &frame_copy );
        cvReleaseCapture( &capture );
    }
    
    // Destroy the window previously created with filename: "Simon"
    cvDestroyWindow("Simon");

    // return 0 to indicate successfull execution of the program
    return 0;
}

/*
void moveRectangles (CvSeq *faces, CvRect *delta) 
{
	cout << "Delta: (" << delta->x << ", " << delta->y << ")\n";

	for(int i = 0; i < (faces ? faces->total : 0); ++i) 
	{
		CvRect* r = (CvRect*)cvGetSeqElem(faces, i);

		cout << "Before: (" << r->x << ", " << r->y << ")\n";

		r->x += delta->x;
		r->y += delta->y;

		cout << "After: (" << r->x << ", " << r->y << ")\n";
	}
}
*/

/*
void drawEyeLine(CvSeq* eyes, IplImage* img)
{
	if(eyes && eyes->total == 2)
	{
		CvRect* r1 = (CvRect*)cvGetSeqElem( eyes, 0 );
		CvRect* r2 = (CvRect*)cvGetSeqElem( eyes, 1 );		
		Vec2f eye1 = findCenter(*r1);
		Vec2f eye2 = findCenter(*r2);
		cvLine(img, Point(eye1), Point(eye2), CV_RGB(0,0,255), 3);
	}	
}
*/

/*
CvRect* getProbable(CvSeq* seq)
{
	int maxN = 0;
	CvRect* max = NULL;
	for(int i = 0; i < (seq ? seq->total : 0); i++ )
    {
        CvAvgComp* avgComp = (CvAvgComp*)cvGetSeqElem( seq, i );
		if(maxN < avgComp->neighbors)
		{
			maxN = avgComp->neighbors;
			max = &avgComp->rect;
		}
	}
	return max;
}
*/

/*
void drawFaces(CvSeq* faces, IplImage* img, CvScalar color) {

	float scale = 1.0f;

	// Create a new image based on the input image
    //IplImage* temp = cvCreateImage( cvSize(img->width/scale,img->height/scale), 8, 3 );

    // Clear the memory storage which was used before
    //cvClearMemStorage( storage );

	// Create two points to represent the face locations
    CvPoint pt1, pt2;
	
	 // Loop the number of faces found.
	
    for(int i = 0; i < (faces ? faces->total : 0); i++ )
    {
        // Create a new rectangle for drawing the face
        CvAvgComp* avgComp = (CvAvgComp*)cvGetSeqElem( faces, i );
		CvRect* r = &avgComp->rect;
        // Find the dimensions of the face,and scale it if necessary
        pt1.x = r->x*scale;
        pt2.x = (r->x+r->width)*scale;
        pt1.y = r->y*scale;
        pt2.y = (r->y+r->height)*scale;

        // Draw the rectangle in the input image
        cvRectangle(img, pt1, pt2, color, 3, 8, 0);
    }
	
    // Release the temp image created.
    //cvReleaseImage( &temp );
}
*/

// Function to detect and draw any faces that is present in an image
void detect_and_draw(IplImage *img)
{
	Rect *lastFaceRectangle = NULL;
	Rect *faceRectangle = NULL;
	
	unique_ptr<DetectedShape> leftEye;
	unique_ptr<DetectedShape> rightEye;
	unique_ptr<DetectedShape> nose;

	DetectedShape *facePointer = NULL;

	if(lastFaceRectangle)
		facePointer = new DetectedShape(faceDetector.detectLikely(Mat(img), *lastFaceRectangle));
	else
		facePointer = new DetectedShape(faceDetector.detectLikely(Mat(img)));

	unique_ptr<DetectedShape> face(facePointer);

	if(face->isValid())
	{
		face->draw(img, CV_RGB(255, 255, 255));

		//float widthArea = 0.3f;
		//float heightArea = 0.3f;
		//CvRect noseROI = {faceRectangle->x + faceRectangle->width * widthArea, faceRectangle->y + faceRectangle->height * heightArea, faceRectangle->width * (1.0f - widthArea), faceRectangle->height * (1.0f - heightArea)};
			
		//cvResetImageROI(img);
		//cvSetImageROI(img, noseROI);
			
		//cvSetImageROI(img, *faceRectangle);

		//cvClearMemStorage( storage );

		//cvResetImageROI(img);
		//cvSetImageROI(img, *faceRectangle);
			


		faceRectangle = &face->getRect();
		float top = 0.25f, bottom = 0.55f, left = 0.1f, right = 0.9f;
		float noseLeft = 0.3f, noseRight = 0.7f, noseTop = 0.5f, noseBottom = 0.8f;

		Rect leftEyeROI(Point(faceRectangle->x + faceRectangle->width * left, faceRectangle->y + faceRectangle->height * top), Point(faceRectangle->width * (right - left) / 2.0f, faceRectangle->height * (bottom - top)));
		Rect rightEyeROI(Point(faceRectangle->x + faceRectangle->width * 0.5f, faceRectangle->y + faceRectangle->height * top), Point(faceRectangle->width * (right - left) / 2.0f, faceRectangle->height * (bottom - top)));
		Rect noseROI(Point(faceRectangle->x + faceRectangle->width * noseLeft, faceRectangle->y + faceRectangle->height * noseTop), Point(faceRectangle->width * (noseRight - noseLeft), faceRectangle->height * (noseBottom - noseTop)));
			
		//cvResetImageROI(img);
		//drawRectangle(&leftEyeROI, img, CV_RGB(175, 175, 175));
		//drawRectangle(&rightEyeROI, img, CV_RGB(175, 0, 175));
		//drawRectangle(&noseROI, img, CV_RGB(0, 175, 175));

		//cvResetImageROI(img);
		//cvSetImageROI(img, noseROI);
		
		unique_ptr<DetectedShape> nose(new DetectedShape(noseDetector.detectLikely(Mat(img), noseROI)));
		nose->draw(img, CV_RGB(0, 0, 255));

		/*
		noseRectangles = cvHaarDetectObjects(img, noseCascade, storage, 1.3, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(20, 20));
		CvRect* noseB = getProbable(noseRectangles); 
		drawRectangle(noseB, img, CV_RGB(0, 0, 255));
		*/

		//cvResetImageROI(img);
		//cvSetImageROI(img, *faceRectangle);

		//faceRectangle->y += faceRectangle->height * 0.10f;
		//faceRectangle->height *= 0.7f;
		//cvResetImageROI(img);
		//cvResetImageROI(img);
		//cvSetImageROI(img, *faceRectangle);
		//cvSetImageROI(img, leftEyeROI);
		//leftEyeRectangles = cvHaarDetectObjects(img, leftEyeCascade, storage, 1.3, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(40, 20));
		//cout << "Found left rectangles: " << leftEyeRectangles->total << "\n";
		//drawRectangle(getProbable(leftEyeRectangles), img, CV_RGB(0, 255, 0));
		//CvRect* leftEyeB = findBiggestRectangle(leftEyeRectangles); 
		//drawRectangle(leftEyeB, img, CV_RGB(0, 255, 0));

		unique_ptr<DetectedShape> leftEye(new DetectedShape(leftEyeDetector.detectLikely(Mat(img), leftEyeROI)));
		leftEye->draw(img, CV_RGB(0, 255, 0));

		/*
		Point2f leftEyeCenter = getCenter(leftEyeB);
		if(leftEyeB)
			cout << "left eye center: x=" << leftEyeCenter.x << ", y=" << leftEyeCenter.y;
		*/

		//cvResetImageROI(img);
		//cvSetImageROI(img, *faceRectangle);
		//cvSetImageROI(img, rightEyeROI);
		//rightEyeRectangles = cvHaarDetectObjects(img, rightEyeCascade, storage, 1.3, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(40, 20));
		//cvClearMemStorage( storage );
		//drawRectangle(getProbable(rightEyeRectangles), img, CV_RGB(255, 0, 0));
		//CvRect* rightEyeB = findBiggestRectangle(rightEyeRectangles); 
		//drawRectangle(rightEyeB, img, CV_RGB(255, 0, 0));
		//Point2f rightEyeCenter = getCenter(rightEyeB);
		//cout << "right eye center: x=" << rightEyeCenter.x << ", y=" << leftEyeCenter.y;

		unique_ptr<DetectedShape> rightEye(new DetectedShape(rightEyeDetector.detectLikely(Mat(img), rightEyeROI)));
		rightEye->draw(img, CV_RGB(255, 0, 0));

		//cvResetImageROI(img);

		faceRectangle->x *= 0.9;
		faceRectangle->y *= 0.9;
		faceRectangle->height *= 1.1;
		faceRectangle->width *= 1.1;
		lastFaceRectangle = faceRectangle;
	}

	// Show the image in the window named "result"
	cvShowImage("Simon", img);
	//cvClearMemStorage( storage );
}