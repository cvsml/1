#include "FMod.h"
#include "Logger.h"

Sound *sound = NULL;

Sound::Sound()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&system);		// Create the main system object.
	if (result != FMOD_OK)
	{
		//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		logger->printLine("FMOD error!");
		system = 0;
	}

	result = system->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
	if (result != FMOD_OK)
	{
		//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		logger->printLine("FMOD error!");
		system = 0;
	}
}

Sound::~Sound()
{
	for(list<FMOD::Sound*>::iterator i = sounds.begin(); i != sounds.end(); ++i)
		(*i)->release();

	if(system)
		system->release();
}

FMOD::Sound* Sound::loadSound(string filePath)
{
	FMOD::Sound *sound;

	FMOD_RESULT result;

	// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	result = system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &sound);		
	//ERRCHECK(result);

	sounds.push_back(sound);

	return sound;
}

void Sound::playSound(FMOD::Sound *sound)
{
	if(!sound)
		return;

	FMOD::Channel *channel;
	FMOD_RESULT result;

	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	//ERRCHECK(result);
}

void Sound::update()
{
	system->update();
}