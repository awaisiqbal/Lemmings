#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "View.h"
#include "SoundSystem.h"
#include "Text.h"


class Lose : public View
{

public:

	//INITIALIZE

	Lose();
	~Lose();
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
	Text text;
	bool exit;
};