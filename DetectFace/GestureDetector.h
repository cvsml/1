#ifndef GESTURE_DETECTOR_H
#define GESTURE_DETECTOR_H

enum DIRECTION {
	DIRECTION_LEFT = 0,
	DIRECTION_CENTER = 1,
	DIRECTION_RIGHT = 2
};

enum GESTURE {
	GESTURE_LEFT = 0,
	GESTURE_CENTER = 1,
	GESTURE_RIGHT = 2,
	GESTURE_LEFT_EYE = 3,
	GESTURE_RIGHT_EYE = 4
};

class GestureDetector {
	const static double LEFT_CHECKPOINT;
	const static double CENTER_LEFT;
	const static double CENTER_CHECKPOINT;
	const static double CENTER_RIGHT;
	const static double RIGHT_CHECKPOINT;

	DIRECTION direction;
	GESTURE gesture;

	GESTURE directionToGesture(DIRECTION direction);

public:
	GestureDetector();
	~GestureDetector();

	GESTURE updateGesture (double ratio, bool leftEyeValidity, bool rightEyeValdity);
	GESTURE getGesture();
	void print(GESTURE gesture);
	void print();
};

#endif

