#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "View.h"
#include "Text.h"
#include "SoundSystem.h"


class Win: public View
{

public:

	//INITIALIZE

	Win();
	~Win();
	void init();
	//void initShaders();

	//OPENGL

	void render();
	void update(int deltaTime);
	void load();

private:

private:
	Texture spritesheet_background;
	Sprite *background;
	int numLemmingsReachedDoor, numLemmingsTotal;
	int time;
	Text text;
	bool exit;
};