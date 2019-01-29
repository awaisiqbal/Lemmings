#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "View.h"


class levelSelection: public View
{



public:

	//INITIALIZE

	levelSelection();
	~levelSelection();
	void init();
	//void initShaders();

	//OPENGL

	void render();
	void update(int deltaTime);
	void load();

	int getLevel();

private:
	void setAnimations();

private:
	Sprite * background;
	Texture spritesheet_background;
	Text text;
	bool exit;
	int level;
};