#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "View.h"
#include "Text.h"


class Instructions: public View
{



public:

	//INITIALIZE

	Instructions();
	~Instructions();
	void init();
	//void initShaders();

	//OPENGL

	void render();
	void update(int deltaTime);
	void load();

private:
	void setAnimations();

private:
	Sprite *background;
	Texture spritesheet_background;
	Text text;
	int time, screen, delay;
	bool b;
	bool controls = false, gameplay = false, exit = false;
};