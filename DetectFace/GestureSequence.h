#ifndef GESTURE_SEQUENCE
#define GESTURE_SEQUENCE

#include <vector>
#include "Gesture.h"

using namespace std;

class GestureSequence {
private:
	vector<Gesture> gestureSequence;
	const static unsigned int sequenceLength;

public:
	GestureSequence();
	~GestureSequence();

	Gesture peek(Gesture gesture);
	void push(Gesture gesture);
	bool operator == (const GestureSequence &other);
};

#endif
