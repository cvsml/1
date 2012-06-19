#include "SequenceRenderer.h"
#include "Gesture.h"
#include "Logger.h"

const double SequenceRenderer::interval = 1;

SequenceRenderer::SequenceRenderer(GestureSequence sequence, MyFrame *frame)
{
	logger->printLine("New turn");
	std::string gestureName = Gesture::Gestures[sequence[0]].getName();
	logger->printLine(gestureName);
	this->sequence = sequence;
	this->frame = frame;
	currentIndex = 0;
	lastTime = time(NULL);
}

SequenceRenderer::~SequenceRenderer()
{

}

void SequenceRenderer::render()
{
	frame->render(sequence[currentIndex]);

	double past = difftime(time(NULL), lastTime);

	if(past >= interval)
	{
		currentIndex++;
		lastTime = time(NULL);

		if(currentIndex < sequence.size())
		{
			std::string gestureName = Gesture::Gestures[sequence[currentIndex]].getName();
			logger->printLine(gestureName);
		}
	}
}

bool SequenceRenderer::done()
{
	if(currentIndex != sequence.size())
		return false;

	frame->render(GESTURE_CENTER);
	return true;
}