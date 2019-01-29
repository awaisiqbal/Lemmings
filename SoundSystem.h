#pragma once

#include "fmod.hpp"

class SoundSystem
{
public:
	SoundSystem() {}


	static SoundSystem &instance()
	{
		static SoundSystem SS;

		return SS;
	}

public:
	~SoundSystem();
	void init();
	void playBackground();
	void playPlay();
	void playButton();
	void playScene(int level);
	void closeSoundSystem();
	void updateSoundSystem();
	void restartSound();
	bool isPlayingPlay();
	bool isPlayingButton();
	bool isPlayingBackground();
private:
	void createSounds();

private:
	FMOD::System *system;
	FMOD::Sound *background, *play, *button, *scene1, *scene2, *scene3;
	FMOD::Channel *channel, *channel1, *channel2, *channel3;
	FMOD_RESULT result;
};

