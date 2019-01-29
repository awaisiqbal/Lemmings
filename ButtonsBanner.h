#pragma once
#include "Sprite.h"
#include "Text.h"


class Scene;

class ButtonsBanner
{
public:
	ButtonsBanner(Scene* s);
	void init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	void updatePosition(int mouseX, int mouseY);
	void checkSkillSelected(glm::vec2 mouse);
	void checkChangeCursor(glm::vec2 mouse);
	~ButtonsBanner();

private:
	enum BannerState
	{
		STATE_1
	};

	BannerState state;
	Texture spritesheet;
	Sprite *sprite;
	Scene* scene;
	Text text;
	string numReachedExitDoor, numLemmingsAlive, numToWin, timeLeft, minutesLeft, secondsLeft;
};

