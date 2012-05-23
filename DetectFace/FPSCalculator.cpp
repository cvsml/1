#include "StdAfx.h"
#include "FPSCalculator.h"

FPSCalculator::FPSCalculator()
{
	fps = frames = 0;
	lastTime = time(NULL);
}


FPSCalculator::~FPSCalculator()
{

}

void FPSCalculator::addFrame()
{
	frames++;

	time_t currentTime = time(NULL);

	double past = difftime(currentTime, lastTime);

	if(past > 1.0)
	{
		fps = frames / past;
		frames = 0;
		lastTime = currentTime;
	}
}

int FPSCalculator::getFPS()
{
	return fps;
}
