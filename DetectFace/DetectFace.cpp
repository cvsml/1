// OpenCV Sample Application: facedetect.c
#include "stdafx.h"

#define _USE_MATH_DEFINES

#include "cv.h"
#include "highgui.h"
#include <opencv2/gpu/gpu.hpp>

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
#include <sstream>

#include "Game.h"

using namespace std;
using namespace cv;

Game game;

// Main function, defines the entry point for the program.
int main(int argc, char** argv)
{
    // Structure for getting video from camera or avi
    CvCapture* capture = 0;

    // Images to capture the frame from video or camera or from file
    IplImage *frame, *frame_copy = 0, *frame_copy_bw = 0;

	game.newGame();

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
			float scale = 640.0f / (float)frame->width;
            if(!frame_copy) {
                //frame_copy = cvCreateImage( cvSize(frame->width,frame->height), IPL_DEPTH_8U, frame->nChannels );
				frame_copy = cvCreateImage(cvSize((int)(frame->width * scale), (int)(frame->height * scale)), IPL_DEPTH_8U, frame->nChannels);
				//frame_copy_bw = cvCreateImage(cvSize(frame->width * scale, frame->height * scale), IPL_DEPTH_8U, 1);
				//cvCvtColor(frame, frame_copy, CV_BGR2GRAY);
			}
			
            // Check the origin of image. If top left, copy the image frame to frame_copy. 
           // if(frame->origin == IPL_ORIGIN_TL)
           //     cvCopy(frame, frame_copy, 0);
            // Else flip and copy the image
           // else
                cvFlip(frame, frame_copy, 1); // Flip around the vertical axis, so the image is mirrored

			//cvCvtColor(frame, frame_copy, CV_BGR2GRAY);
			//cvResize(frame, frame_copy, scale);
			//cvCvtColor(frame, frame_copy_bw, CV_BGR2GRAY);

			//cvEqualizeHist(frame_copy, frame_copy);

			game.update(frame_copy);

            // Wait for a while before proceeding to the next frame
            if(cvWaitKey(1) >= 0 )
                break;
			
			game.draw(frame_copy);
        }

        // Release the images, and capture memory
        cvReleaseImage(&frame_copy);
        cvReleaseCapture(&capture);
    }
    
    // Destroy the window previously created with filename: "Simon"
    cvDestroyWindow("Simon");

    // return 0 to indicate successfull execution of the program
    return 0;
}