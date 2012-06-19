#ifndef SEQUENCE_RENDERER_H
#define SEQUENCE_RENDERER_H

#include <time.h>
#include "ImagePane.h"
#include "GestureSequence.h"
#include "MyFrame.h"

//class MyFrame;
class SequenceRenderer {
private:
	GestureSequence sequence;
	MyFrame *frame;

	const static double interval;
	int currentIndex;
	time_t lastTime;

public:
	SequenceRenderer(GestureSequence sequence, MyFrame *frame);
	~SequenceRenderer();

	void render();
	bool done();
};

#endif