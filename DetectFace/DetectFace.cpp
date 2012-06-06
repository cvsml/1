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
#include "Face.h"
#include "GestureDetector.h"

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

Face faceContainer;
GestureDetector gesture;

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
			//printf("FPS: %d\n", fps.getFPS());
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

// Function to detect and draw any faces that is present in an image
void detect_and_draw(IplImage *img)
{
	static Rect lastFaceRectangle(0, 0, 0, 0);
	Rect faceRectangle;

	Rect tmp = faceDetector.detectLikely(Mat(img), lastFaceRectangle);
	if(!tmp.area())
		tmp = faceDetector.detectLikely(Mat(img));

	faceContainer.getFaceArea()->setRect(tmp);
	faceRectangle = faceContainer.getFaceArea()->getRect();

	if(faceContainer.getFaceArea()->isValid())
	{
		faceContainer.getFaceArea()->draw(img, CV_RGB(255, 255, 255));	
		
		float top = 0.25f, bottom = 0.55f, left = 0.1f, right = 0.9f;
		float noseLeft = 0.3f, noseRight = 0.7f, noseTop = 0.5f, noseBottom = 0.8f;

		// Absolute
		Rect leftEyeROI(Point(faceRectangle.x + faceRectangle.width * left, faceRectangle.y + faceRectangle.height * top), Size(faceRectangle.width * (right - left) / 2.0f, faceRectangle.height * (bottom - top)));
		Rect rightEyeROI(Point(faceRectangle.x + faceRectangle.width * 0.5f, faceRectangle.y + faceRectangle.height * top), Size(faceRectangle.width * (right - left) / 2.0f, faceRectangle.height * (bottom - top)));
		Rect noseROI(Point(faceRectangle.x + faceRectangle.width * noseLeft, faceRectangle.y + faceRectangle.height * noseTop), Size(faceRectangle.width * (noseRight - noseLeft), faceRectangle.height * (noseBottom - noseTop)));

		faceContainer.getNoseArea()->setRect(noseDetector.detectLikely(Mat(img), noseROI));
		faceContainer.getNoseArea()->draw(img, CV_RGB(0, 0, 255));

		// The image is flipped, so left eye needs to search on the right side, and vice verca
		faceContainer.getLeftEyeArea()->setRect(leftEyeDetector.detectLikely(Mat(img), rightEyeROI));
		faceContainer.getLeftEyeArea()->draw(img, CV_RGB(0, 255, 0));

		faceContainer.getRightEyeArea()->setRect(rightEyeDetector.detectLikely(Mat(img), leftEyeROI));
		faceContainer.getRightEyeArea()->draw(img, CV_RGB(255, 0, 0));

		faceRectangle.x = MAX(0.0f, faceRectangle.x - 30);
		faceRectangle.y = MAX(0.0f, faceRectangle.y - 30);
		faceRectangle.width = MIN(img->width - faceRectangle.x, faceRectangle.width + 60);
		faceRectangle.height = MIN(img->height - faceRectangle.y, faceRectangle.height + 60);
		lastFaceRectangle = faceRectangle;

		//cvRectangle(img, lastFaceRectangle.tl(), lastFaceRectangle.br(), CV_RGB(255, 0, 255), 3);

//		if(faceContainer.getLeftEyeArea()->isValid() && faceContainer.getRightEyeArea()->isValid() && faceContainer.getNoseArea()->isValid())
//		{
			double ratio = faceContainer.getRatio();
			//printf("New Ratio: %.2f, Old Ratio: %.2f\n", ratio, faceContainer.getRatioOld());

			gesture.updateGesture(ratio, faceContainer.getLeftEyeArea()->isValid(), faceContainer.getRightEyeArea()->isValid());
			gesture.print();

			/*float leftAngle = faceContainer.getLeftAngle();
			float rightAngle = faceContainer.getRightAngle();

			printf("Left angle: %2f, ", leftAngle);
			printf("Right angle: %2f\n", rightAngle);

			string side = "center";

			if(leftAngle > 57)
				side = "left";

			if(rightAngle > 57)
				side = "right";

			printf("Side: %s\n", side.c_str()); */
//		}
//		else
//		{
//			cout << "Invalid" << endl;
//		}
	}

	// Show the image in the window named "result"
	cvShowImage("Simon", img);
}