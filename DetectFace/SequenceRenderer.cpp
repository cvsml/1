#include "SequenceRenderer.h"

const double SequenceRenderer::interval = 0.25f;

SequenceRenderer::SequenceRenderer(GestureSequence *sequence, ImagePane *lookLeft, ImagePane *lookRight, ImagePane *eyeLeft, ImagePane *eyeRight,
					 wxBitmap *lookLeftBitmap, wxBitmap *lookRightBitmap, wxBitmap *eyeLeftBitmap, wxBitmap *eyeRightBitmap, wxBitmap *defaultBitmap)
{
	this->sequence = sequence;
	this->lookLeftPane = lookLeft;
	this->lookRightPane = lookRight;
	this->eyeLeftPane = eyeLeft;
	this->eyeRightPane = eyeRight;
	this->lookLeftBitmap = lookLeftBitmap;
	this->lookRightBitmap = lookRightBitmap;
	this->eyeLeftBitmap = eyeLeftBitmap;
	this->eyeRightBitmap = eyeRightBitmap;
	this->defaultBitmap = defaultBitmap;

	currentIndex = 0;
	lastTime = time(NULL);
}

SequenceRenderer::~SequenceRenderer()
{

}

void SequenceRenderer::render(GESTURE gesture)
{
	lookLeftPane->setImage(*defaultBitmap);
	lookRightPane->setImage(*defaultBitmap);
	eyeLeftPane->setImage(*defaultBitmap);
	eyeRightPane->setImage(*defaultBitmap);

	switch(gesture)
	{
		case GESTURE_CENTER:

		break;

		case GESTURE_LEFT:
			lookLeftPane->setImage(*lookLeftBitmap);
		break;

		case GESTURE_RIGHT:
			lookRightPane->setImage(*lookRightBitmap);
		break;

		case GESTURE_LEFT_EYE:
			eyeLeftPane->setImage(*eyeLeftBitmap);
		break;

		case GESTURE_RIGHT_EYE:
			eyeRightPane->setImage(*eyeRightBitmap);
		break;

		default:

		break;
	}
}

void SequenceRenderer::render()
{
	render((*sequence)[currentIndex]);

	double past = difftime(time(NULL), lastTime);

	if(past >= interval)
	{
		currentIndex++;
		lastTime = time(NULL);
	}
}

bool SequenceRenderer::done()
{
	return currentIndex == sequence->size();
}