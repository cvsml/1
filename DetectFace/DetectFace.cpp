// OpenCV Sample Application: facedetect.c
#include "stdafx.h"

#define _USE_MATH_DEFINES

// Include header files
#include "cv.h"
#include "highgui.h"
#include "FPSCalculator.h"

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

using namespace std;
using namespace cv;

// Create memory for calculations
static CvMemStorage* storage = 0;

// Create a new Haar classifier
static CvHaarClassifierCascade* faceCascade = 0;
static CvHaarClassifierCascade* leftEyeCascade = 0;
static CvHaarClassifierCascade* rightEyeCascade = 0;
static CvHaarClassifierCascade* noseCascade = 0;

// Function prototype for detecting and drawing an object from an image
CvSeq* detect_and_draw( IplImage* image );
void drawFaces(CvSeq* faces, IplImage* img, CvScalar color);

// Create a string that contains the cascade name
const char* cascadeFacePath = "haarcascade_frontalface_alt2.xml";
const char* cascadeLeftEyePath = "haarcascade_mcs_righteye.xml";
const char* cascadeRightEyePath = "haarcascade_mcs_lefteye.xml";
const char* cascadeNosePath = "haarcascade_mcs_nose.xml";

CvSeq *faceRectangles = 0;
CvSeq *leftEyeRectangles = 0;
CvSeq *rightEyeRectangles = 0;
CvSeq *noseRectangles = 0;
FPSCalculator fps;

int skipFrames = 1;

// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{

    // Structure for getting video from camera or avi
    CvCapture* capture = 0;

    // Images to capture the frame from video or camera or from file
    IplImage *frame, *frame_copy = 0;

    // Used for calculations
    int optlen = strlen("--cascade=");

    // Input file name for avi or image file.
    const char* input_name;

    // Check for the correct usage of the command line
    if( argc > 1 && strncmp( argv[1], "--cascade=", optlen ) == 0 )
    {
        cascadeFacePath = argv[1] + optlen;
        input_name = argc > 2 ? argv[2] : 0;
    }
    else
    {
		input_name = argc > 1 ? argv[1] : 0;
    }

    // Load the HaarClassifierCascade
    faceCascade = (CvHaarClassifierCascade*)cvLoad( cascadeFacePath, 0, 0, 0 );
    leftEyeCascade = (CvHaarClassifierCascade*)cvLoad( cascadeLeftEyePath, 0, 0, 0 );
	rightEyeCascade = (CvHaarClassifierCascade*)cvLoad( cascadeRightEyePath, 0, 0, 0 );
	noseCascade = (CvHaarClassifierCascade*)cvLoad( cascadeNosePath, 0, 0, 0 );

    // Check whether the cascade has loaded successfully. Else report and error and quit
    if(!faceCascade || !leftEyeCascade || !rightEyeCascade || !noseCascade)
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade(s)\n" );
		getchar();
        return -1;
    }
    
    // Allocate the memory storage
    storage = cvCreateMemStorage(0);
    
    // Find whether to detect the object from file or from camera.
    if( !input_name || (isdigit(input_name[0]) && input_name[1] == '\0') )
        capture = cvCaptureFromCAM( !input_name ? 0 : input_name[0] - '0' );
    else
        capture = cvCaptureFromAVI( input_name ); 

    // Create a new named window with title: result
    cvNamedWindow( "result", 1 );

    // Find if the capture is loaded successfully or not.

	int index = 0;
    // If loaded succesfully, then:
    if( capture )
    {
        // Capture from the camera.
        for(;;)
        {		
            // Capture the frame and load it in IplImage
            if( !cvGrabFrame( capture ))
                break;
			
            frame = cvRetrieveFrame(capture);

            // If the frame does not exist, quit the loop
            if( !frame )
                break;
            
            // Allocate framecopy as the same size of the frame
            if( !frame_copy ) {
                frame_copy = cvCreateImage( cvSize(frame->width,frame->height), IPL_DEPTH_8U, frame->nChannels );
				//frame_copy = cvCreateImage(cvSize(frame->width, frame->height), 8, 1);
				//cvCvtColor(frame, frame_copy, CV_BGR2GRAY);
			}
			
            // Check the origin of image. If top left, copy the image frame to frame_copy. 
            if( frame->origin == IPL_ORIGIN_TL )
                cvCopy( frame, frame_copy, 0 );
            // Else flip and copy the image
            else
                cvFlip( frame, frame_copy, 0 );

			if(index % skipFrames == 0) {
				// Call the function to detect and draw the face
				faceRectangles = detect_and_draw( frame_copy );
			} else {
			//	drawFaces(faceRectangles, frame_copy);
				cvShowImage( "result", frame_copy );
			}
			
            // Wait for a while before proceeding to the next frame
            if(cvWaitKey(1) >= 0 )
                break;
			
			index++;
			fps.addFrame();
			printf("FPS: %d\n", fps.getFPS());
        }

        // Release the images, and capture memory
        cvReleaseImage( &frame_copy );
        cvReleaseCapture( &capture );
    }
    
    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("result");

    // return 0 to indicate successfull execution of the program
    return 0;
}

CvRect* findBiggestRectangle (CvSeq *faces) 
{	
	CvRect *result = NULL;
	int largestArea = 0;

	for(int i = 0; i < (faces ? faces->total : 0); i++ )
    {
        CvRect* r = (CvRect*)cvGetSeqElem(faces, i);
		int area = r->width * r->height;

		if (area > largestArea)
			result = r;
	}

	return result;
}

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



Mat findCenter(const CvRect &r)
{
	Mat m(3, 1, DataType<float>::type);

	double *data = m.ptr<double>(0);

	data[0] = r.x + r.width / 2.0f;
	data[1] = r.y + r.height / 2.0f;
	data[2] = 0;

	return m;
}

float dot(Mat vec1, Mat vec2)
{
	double *vec1Data = vec1.ptr<double>(0);
	double *vec2Data = vec2.ptr<double>(0);

	return vec1Data[0]*vec2Data[0] + vec1Data[1]*vec2Data[1] + vec1Data[2]*vec2Data[2];
}

double getDegree(Mat &vec1, Mat &vec2)
{
	float lengthVec1;
	double *originalVec1 = vec1.ptr<double>(0);
	lengthVec1  = sqrt(originalVec1[0]*originalVec1[0] + originalVec1[1]*originalVec1[1] + originalVec1[2]*originalVec1[2]);
	if(!lengthVec1)
	{
		cout << "Etempt to devide by zero";
		return 0;
	}
	cv::Mat normVec1(3, 1, DataType<float>::type);
	double *newVec1 = normVec1.ptr<double>(0);
	newVec1[0] = originalVec1[0]/lengthVec1;
	newVec1[1] = originalVec1[1]/lengthVec1;
	newVec1[2] = originalVec1[2]/lengthVec1;


	float lengthVec2;
	double *originalVec2 = vec2.ptr<double>(0);
	lengthVec2  = sqrt(originalVec2[0]*originalVec2[0] + originalVec2[1]*originalVec2[1] + originalVec2[2]*originalVec2[2]);
	if(!lengthVec2)
	{
		cout << "Etempt to devide by zero";
		return 0;
	}
	cv::Mat normVec2(3, 1, DataType<float>::type);
	double *newVec2 = normVec2.ptr<double>(0);
	newVec2[0] = originalVec2[0]/lengthVec2;
	newVec2[1] = originalVec2[1]/lengthVec2;
	newVec2[2] = originalVec2[2]/lengthVec2;

	double cosDeg = dot(normVec1, normVec2);

	return acos(cosDeg)*180.0/M_PI;
}

double getDegree(const CvRect &rec1, const CvRect &rec2, const CvRect &rec3)
{
	Mat center1 = findCenter(rec1);
	Mat center2 = findCenter(rec2);
	Mat center3 = findCenter(rec3);

	Mat vec1 = center2 - center1;
	Mat vec2 = center3 - center1;
	return getDegree(vec1, vec2);
}

void drawEyeLine(CvSeq* eyes, IplImage* img)

{
	if(eyes && eyes->total == 2)
	{
		CvRect* r1 = (CvRect*)cvGetSeqElem( eyes, 0 );
		CvRect* r2 = (CvRect*)cvGetSeqElem( eyes, 1 );		
		Mat eye1 = findCenter(*r1);
		Mat eye2 = findCenter(*r2);
		CvPoint pt1 = {eye1.ptr<double>(0)[0], eye1.ptr<double>(0)[1]};
		CvPoint pt2 = {eye2.ptr<double>(0)[0], eye2.ptr<double>(0)[1]};
		//printf("eyes degree: %f \n", getDegree(*r1, *r2));
		cvLine(img, pt1, pt2, CV_RGB(0,0,255), 3);
	}	
}

void drawRectangle(CvRect *r, IplImage* img, CvScalar color) {

	if(r == NULL)
		return;

	// Create two points to represent the face locations
    CvPoint pt1, pt2;

    // Find the dimensions of the face,and scale it if necessary
    pt1.x = r->x;
    pt2.x = r->x + r->width;
    pt1.y = r->y;
    pt2.y = r->y + r->height;

    // Draw the rectangle in the input image
    cvRectangle(img, pt1, pt2, color, 3);
}

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
        cvRectangle( img, pt1, pt2, color, 3, 8, 0 );
    }
	
	/*
	CvRect* r = getProbable(faces);
	if(r != NULL)
		drawRectangle(*r,img, color);
		*/
    // Release the temp image created.
    //cvReleaseImage( &temp );
}

// Function to detect and draw any faces that is present in an image
CvSeq* detect_and_draw( IplImage* img )
{
	int scale = 1;

	CvSeq *faces = 0;

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( faceCascade )
    {      
		faces = cvHaarDetectObjects(img, faceCascade, storage, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize(40, 40) );
		//cvClearMemStorage( storage );

		//CvRect *faceRectangle = findBiggestRectangle(faces);
		CvRect *faceRectangle = getProbable(faces);
		if(faceRectangle)
		{
			drawRectangle(faceRectangle, img, CV_RGB(255, 255, 255));

			float widthArea = 0.3f;
			float heightArea = 0.3f;
			//CvRect noseROI = {faceRectangle->x + faceRectangle->width * widthArea, faceRectangle->y + faceRectangle->height * heightArea, faceRectangle->width * (1.0f - widthArea), faceRectangle->height * (1.0f - heightArea)};
			
			//cvResetImageROI(img);
			//cvSetImageROI(img, noseROI);
			
			cvSetImageROI(img, *faceRectangle);


			//cvClearMemStorage( storage );

			//cvResetImageROI(img);
			//cvSetImageROI(img, *faceRectangle);
			

			

			float top = 0.25f, bottom = 0.55f, left = 0.1f, right = 0.9f;
			float noseLeft = 0.3f, noseRight = 0.7f, noseTop = 0.5f, noseBottom = 0.8f;
			CvRect leftEyeROI = {faceRectangle->x + faceRectangle->width * left, faceRectangle->y + faceRectangle->height * top, faceRectangle->width * (right - left) / 2.0f, faceRectangle->height * (bottom - top)};
			CvRect rightEyeROI = {faceRectangle->x + faceRectangle->width * 0.5f, faceRectangle->y + faceRectangle->height * top, faceRectangle->width * (right - left) / 2.0f, faceRectangle->height * (bottom - top)};
			CvRect noseROI = {faceRectangle->x + faceRectangle->width * noseLeft, faceRectangle->y + faceRectangle->height * noseTop, faceRectangle->width * (noseRight - noseLeft), faceRectangle->height * (noseBottom - noseTop)};
			
			cvResetImageROI(img);
			drawRectangle(&leftEyeROI, img, CV_RGB(175, 175, 175));
			drawRectangle(&rightEyeROI, img, CV_RGB(175, 0, 175));
			drawRectangle(&noseROI, img, CV_RGB(0, 175, 175));

			cvResetImageROI(img);
			cvSetImageROI(img, noseROI);
			noseRectangles = cvHaarDetectObjects(img, noseCascade, storage, 1.15, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(10, 20));
			drawRectangle(getProbable(noseRectangles), img, CV_RGB(0, 0, 255));

			//cvResetImageROI(img);
			//cvSetImageROI(img, *faceRectangle);

			//faceRectangle->y += faceRectangle->height * 0.10f;
			//faceRectangle->height *= 0.7f;
			//cvResetImageROI(img);
			cvResetImageROI(img);
			//cvSetImageROI(img, *faceRectangle);
			cvSetImageROI(img, leftEyeROI);
			leftEyeRectangles = cvHaarDetectObjects(img, leftEyeCascade, storage, 1.15, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(50, 25));
			cout << "Found left rectangles: " << leftEyeRectangles->total << "\n";
			drawRectangle(getProbable(leftEyeRectangles), img, CV_RGB(0, 255, 0));

			cvResetImageROI(img);
			//cvSetImageROI(img, *faceRectangle);
			cvSetImageROI(img, rightEyeROI);
			rightEyeRectangles = cvHaarDetectObjects(img, rightEyeCascade, storage, 1.15, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(50, 25));
			//cvClearMemStorage( storage );
			drawRectangle(getProbable(rightEyeRectangles), img, CV_RGB(255, 0, 0));

			cvResetImageROI(img);
		}

		// Show the image in the window named "result"
		cvShowImage( "result", img );
		cvClearMemStorage( storage );
    }

	return faces;
}