#ifndef FPS_CALCULATOR_H
#define FPS_CALCULATOR_H

#include <time.h>

class FPSCalculator {
private:
	int fps;
	double frames;
	time_t lastTime;

public:
	FPSCalculator();
	~FPSCalculator();

	void addFrame();
	int getFPS();
};

#endif
