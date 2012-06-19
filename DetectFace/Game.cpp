#include "StdAfx.h"
#include "cv.h"
#include "highgui.h"
#include <opencv2/gpu/gpu.hpp>

#include "Game.h"
#include <iostream>

const unsigned int Game::victorySequenceLength = 4;

using namespace cv;

Game::Game() : faceDetector("haarcascade_frontalface_alt2.xml", 1.4f), 
			   leftEyeDetector("haarcascade_mcs_lefteye.xml", 1.1f, 3), 
			   rightEyeDetector("haarcascade_mcs_righteye.xml", 1.1f, 3), 
			   noseDetector("haarcascade_mcs_nose.xml", 1.1f, 3, CV_HAAR_SCALE_IMAGE, Size(30, 30))
{
	 // Check whether the cascade has loaded successfully. Else report and error and quit
	if(!(faceDetector.isValid() && leftEyeDetector.isValid() && rightEyeDetector.isValid() && noseDetector.isValid()))
    {
        fprintf(stderr, "ERROR: Could not load classifier cascade(s)\n");
		getchar();
    }
    
	previousGesture = GESTURE_CENTER;
	newTurnFlag = false;
}

Game::~Game()
{

}

void Game::newGame()
{
	cout << "NEW GAME" << endl;
	sequence.reset();
	newTurn();
}

bool Game::checkVictory()
{
	if(sequence.size() == victorySequenceLength)
	{
		cout << "YOU WON! Yay!!" << endl << "--------------" <<  endl;
		newGame();
		return true;
	}

	return false;
}

void Game::newTurn()
{
	if(checkVictory())
		return;
	
	sequence.push(generator.nextGesture());
	sequence.print();
	index = 0;
	newTurnFlag = true;
}

void Game::handleGesture(GESTURE newGesture)
{
	// If I got center, then the previous is center
	if(newGesture == GESTURE_CENTER)
	{
		previousGesture = GESTURE_CENTER;
		return;
	}

	// I didn't get center, and the previous gesture is not center, ignore it
	if(previousGesture != GESTURE_CENTER)
	{
		return;
	}

	// Now we didn't get center, and the previous IS center
	if(newGesture == sequence[index])
	{
		index++;
		cout << "Ding!" << endl;

		if(index == sequence.size())
			newTurn();
	}

	else
	{
		cout << "EPIC FAIL!" << endl;
		newGame();
	}
}

void Game::update(IplImage *img)
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
		
		float top = 0.20f, bottom = 0.55f, left = 0.0f, right = 1.0f;
		float noseLeft = 0.2f, noseRight = 0.8f, noseTop = 0.4f, noseBottom = 0.9f;

		// Absolute
		Rect leftEyeROI(Point2f(faceRectangle.x + faceRectangle.width * left + faceRectangle.width * 0.1f, faceRectangle.y + faceRectangle.height * top), Size_<float>(faceRectangle.width * (right - left) / 2.0f, faceRectangle.height * (bottom - top)));
		Rect rightEyeROI(Point2f(faceRectangle.x + faceRectangle.width * 0.5f - faceRectangle.width * 0.1f, faceRectangle.y + faceRectangle.height * top), Size_<float>(faceRectangle.width * (right - left) / 2.0f, faceRectangle.height * (bottom - top)));
		Rect noseROI(Point2f(faceRectangle.x + faceRectangle.width * noseLeft, faceRectangle.y + faceRectangle.height * noseTop), Size_<float>(faceRectangle.width * (noseRight - noseLeft), faceRectangle.height * (noseBottom - noseTop)));

		faceContainer.getNoseArea()->setRect(noseDetector.detectLikely(Mat(img), noseROI));
		faceContainer.getNoseArea()->draw(img, CV_RGB(0, 0, 255));

		// The image is flipped, so left eye needs to search on the right side, and vice verca
		faceContainer.getLeftEyeArea()->setRect(leftEyeDetector.detectLikely(Mat(img), leftEyeROI));
		faceContainer.getLeftEyeArea()->draw(img, CV_RGB(0, 255, 0));

		faceContainer.getRightEyeArea()->setRect(rightEyeDetector.detectLikely(Mat(img), rightEyeROI));
		faceContainer.getRightEyeArea()->draw(img, CV_RGB(255, 0, 0));

		faceRectangle.x = max(0, faceRectangle.x - 30);
		faceRectangle.y = max(0, faceRectangle.y - 30);
		faceRectangle.width = min(img->width - faceRectangle.x, faceRectangle.width + 60);
		faceRectangle.height = min(img->height - faceRectangle.y, faceRectangle.height + 60);
		lastFaceRectangle = faceRectangle;

		double ratio = faceContainer.getRatio();
		gesture.updateGesture(ratio, faceContainer.isLeftEyeValid(), faceContainer.isRightEyeValid(), faceContainer.isNoseValid());

		if(gesture.newGesture())
		{
			handleGesture(gesture.getGesture());
		}

		/*
		cvRectangle(img, rightEyeROI.tl(), rightEyeROI.br(), CV_RGB(255, 255, 255), 3);
		cvRectangle(img, leftEyeROI.tl(), leftEyeROI.br(), CV_RGB(255, 255, 255), 3);
		cvRectangle(img, noseROI.tl(), noseROI.br(), CV_RGB(255, 255, 255), 3);
		cvRectangle(img, lastFaceRectangle.tl(), lastFaceRectangle.br(), CV_RGB(255, 0, 255), 3);
		*/
	}

	fps.addFrame();
}

void Game::draw(IplImage *img)
{
	stringstream stream;
	stream << "FPS: " << fps.getFPS();

	putText(Mat(img), stream.str().c_str(), Point(50, 50), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(255, 0, 0), 2);
	cvShowImage("Simon", img);
}

std::string Game::getFPS()
{
	stringstream stream;
	stream << fps.getFPS();
	return stream.str();
}

bool Game::isNewTurn()
{
	if(!newTurnFlag)
		return false;

	newTurnFlag = false;
	return true;
}