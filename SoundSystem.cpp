#include <glm/glm.hpp>
#include "SoundSystem.h"

SoundSystem::~SoundSystem()
{
}

void SoundSystem::init()
{
	result = FMOD::System_Create(&system);
	channel = 0;
	channel1 = 0;
	result = system->init(2, FMOD_INIT_NORMAL, NULL);
	createSounds();
}

void SoundSystem::createSounds()
{
	result = system->createSound("music/tim2.mp3", FMOD_DEFAULT, 0, &background);
	background->setMode(FMOD_LOOP_NORMAL);
	background->setLoopCount(-1);

	result = system->createSound("music/letsgo.mp3", FMOD_DEFAULT, 0, &play);
	result = system->createSound("music/button.wav", FMOD_DEFAULT, 0, &button);

	result = system->createSound("music/scene1.mp3", FMOD_DEFAULT, 0, &scene1);
	scene1->setMode(FMOD_LOOP_NORMAL);
	scene1->setLoopCount(-1);

	result = system->createSound("music/scene2.mp3", FMOD_DEFAULT, 0, &scene2);
	scene2->setMode(FMOD_LOOP_NORMAL);
	scene2->setLoopCount(-1);

	result = system->createSound("music/scene3.mp3", FMOD_DEFAULT, 0, &scene3);
	scene3->setMode(FMOD_LOOP_NORMAL);
	scene3->setLoopCount(-1);
}


void SoundSystem::playBackground()
{
	system->playSound(background, 0, false, &channel);
}

void SoundSystem::playPlay()
{
	system->playSound(play, 0, false, &channel1);
}

void SoundSystem::playButton()
{
	
	system->playSound(button, 0, false, &channel2);
}

void SoundSystem::playScene(int level)

{

	if (level == 0) system->playSound(scene1, 0, false, &channel3);
	else if (level == 1) system->playSound(scene2, 0, false, &channel3);
	else if (level == 2) system->playSound(scene3, 0, false, &channel3);
}



void SoundSystem::closeSoundSystem()
{
	restartSound();
	background->release();
	button->release();
	play->release();
	scene1->release();
	scene2->release();
	scene3->release();
	system->release();
	system->close();
}

void SoundSystem::updateSoundSystem()
{
	system->update();
}


void SoundSystem::restartSound()
{
	if (channel != NULL) channel->stop();
	if (channel1 != NULL) channel1->stop();
	if (channel2 != NULL) channel2->stop();
	if (channel3 != NULL) channel3->stop();
	
}

bool SoundSystem::isPlayingPlay()
{
	bool b = false;
	channel1->isPlaying(&b);
	return b;
}
bool SoundSystem::isPlayingButton()
{
	bool b = false;
	channel2->isPlaying(&b);
	return b;
}

bool SoundSystem::isPlayingBackground()
{
	bool b = false;
	channel->isPlaying(&b);
	return b;
}
