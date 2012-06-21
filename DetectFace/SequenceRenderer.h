#ifndef SEQUENCE_RENDERER_H
#define SEQUENCE_RENDERER_H

#include <time.h>
#include "ImagePane.h"
#include "GestureSequence.h"
#include "MyFrame.h"

class SequenceRenderer {
private:

	GestureSequence sequence;
	MyFrame *frame;
	GESTURE currentGesture;

	int currentIndex;
	time_t lastTime;

	void render(GESTURE gesture);

public:
	SequenceRenderer(GestureSequence sequence, MyFrame *frame);
	~SequenceRenderer();

	const static double interval;
	const static double pause;

	void render();
	bool done();
};

#endif