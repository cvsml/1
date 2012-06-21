#ifndef FMOD_H
#define FMOD_H

#include "fmod.hpp"
#include <string>
#include <list>

using namespace std;

class Sound {
private:
	FMOD::System *system;
	list<FMOD::Sound*> sounds;

public:
	Sound();
	~Sound();

	FMOD::Sound* loadSound(string);
	void playSound(FMOD::Sound*);
	void update();
};

extern Sound *sound;

#endif