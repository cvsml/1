#ifndef GESTURE_DETECTOR_H
#define GESTURE_DETECTOR_H

enum MODES {
	MODE_LEFT = 0,
	MODE_CENTER = 1,
	MODE_RIGHT = 2
};

class GestureDetector {
	const static double LEFT_CHECKPOINT;
	const static double CENTER_LEFT;
	const static double CENTER_CHECKPOINT;
	const static double CENTER_RIGHT;
	const static double RIGHT_CHECKPOINT;
	MODES mode;

public:
	GestureDetector();
	~GestureDetector();

	MODES updateMode (double ratio);
	MODES getMode();
	void printMode(MODES mode);
	void printMode();
};

#endif

