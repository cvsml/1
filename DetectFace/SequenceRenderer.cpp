#include "SequenceRenderer.h"
#include "Gesture.h"
#include "Logger.h"

const double SequenceRenderer::interval = 0.7;
const double SequenceRenderer::pause = 0.4;

SequenceRenderer::SequenceRenderer(GestureSequence sequence, MyFrame *frame)
{
	logger->printLine("New turn");
	std::string gestureName = Gesture::Gestures[sequence[0]].getName();
	logger->printLine(gestureName);
	this->sequence = sequence;
	this->frame = frame;
	currentIndex = 0;
	currentGesture = sequence[currentIndex];
	lastTime = time(NULL);
}

SequenceRenderer::~SequenceRenderer()
{

}

void SequenceRenderer::render()
{
	frame->render(currentGesture);

	time_t currentTime = time(NULL);
	double past = difftime(currentTime, lastTime);

	// Done with pause state, move on
	if(past >= (interval + pause))
	{
		currentIndex++;
		lastTime = currentTime;
		currentGesture = sequence[currentIndex];

		if(currentIndex < sequence.size())
		{
			std::string gestureName = Gesture::Gestures[sequence[currentIndex]].getName();
			logger->printLine(gestureName);
		}
	}

	// Need to enter pause state
	else if(past >= interval)
	{
		currentGesture = GESTURE_CENTER;
		//logger->printLine("Will render DEFAULT in next frame");
	}
}

bool SequenceRenderer::done()
{
	if(currentIndex != sequence.size())
		return false;

	frame->render(GESTURE_CENTER);
	return true;
}