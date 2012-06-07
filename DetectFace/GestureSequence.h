#ifndef GESTURE_SEQUENCE
#define GESTURE_SEQUENCE

#include <vector>
#include "Gestures.h"

using namespace std;

class GestureSequence {
private:
	vector<GESTURE> gestureSequence;
	const static unsigned int sequenceLength;

public:
	GestureSequence();
	~GestureSequence();

	GESTURE peek(GESTURE gesture);
	void push(GESTURE gesture);
	bool operator = (const GestureSequence &other);
};

#endif
