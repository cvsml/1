#ifndef GESTURE_H
#define GESTURE_H

#include <string>
using namespace std;

enum DIRECTION {
	DIRECTION_LEFT,
	DIRECTION_CENTER,
	DIRECTION_RIGHT
};

enum GESTURE {
	GESTURE_LEFT,
	GESTURE_CENTER,
	GESTURE_RIGHT,
	GESTURE_LEFT_EYE,
	GESTURE_RIGHT_EYE
};

class Gesture {
private:
	GESTURE type;
	string imagePath, name;

public:
	Gesture();
	Gesture(GESTURE type, string name, string imagePath);
	~Gesture();

	static Gesture Gestures[5];

	GESTURE getValue();
	void print();
	void draw();
	bool operator == (const Gesture &other);
	bool operator != (const Gesture &other);

};

#endif

