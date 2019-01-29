#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "View.h"


class Credits: public View
{



public:

	//INITIALIZE

	Credits();
	~Credits();
	void init();
	//void initShaders();

	//OPENGL

	void render();
	void update(int deltaTime);
	void load();

private:
	void setAnimations();

private:
	Sprite * background;
	Texture spritesheet_background;
	Text text;
	bool exit;
};