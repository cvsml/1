#ifndef GESTURE_SEQUENCE
#define GESTURE_SEQUENCE

#include <vector>
#include "Gesture.h"

using namespace std;

class GestureSequence {
private:
	vector<GESTURE> gestureSequence;

public:
	GestureSequence();
	~GestureSequence();
	void reset();

	GESTURE peek();
	GESTURE operator [](int i);
	void push(GESTURE gesture);
	bool operator == (const GestureSequence &other);
	void print();
	int size();
};

#endif
