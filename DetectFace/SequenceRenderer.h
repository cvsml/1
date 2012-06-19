#ifndef SEQUENCE_RENDERER_H
#define SEQUENCE_RENDERER_H

#include <time.h>
#include "ImagePane.h"
#include "GestureSequence.h"

class SequenceRenderer {
private:
	ImagePane *lookLeftPane;
	ImagePane *lookRightPane;
	ImagePane *eyeLeftPane;
	ImagePane *eyeRightPane;

	wxBitmap *lookLeftBitmap;
	wxBitmap *lookRightBitmap;
	wxBitmap *eyeLeftBitmap;
	wxBitmap *eyeRightBitmap;
	wxBitmap *defaultBitmap;

	GestureSequence *sequence;

	const static double interval;
	int currentIndex;
	time_t lastTime;

	void render(GESTURE gesture);

public:
	SequenceRenderer(GestureSequence *sequence, ImagePane *lookLeft, ImagePane *lookRight, ImagePane *eyeLeft, ImagePane *eyeRight,
					 wxBitmap *lookLeftBitmap, wxBitmap *lookRightBitmap, wxBitmap *eyeLeftBitmap, wxBitmap *eyeRightBitmap, wxBitmap *defaultBitmap);
	~SequenceRenderer();

	void render();
	bool done();
};

#endif