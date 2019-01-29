#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "View.h"


class Menu: public View
{

	#define KEY_ENTER 13
	#define KEY_N 110
	#define KEY_I 105
	#define KEY_C 99
	#define KEY_L 108

	enum Bubleft
	{
		IDLLEFT, KISS
	};

	enum Bubright
	{
		IDLRIGHT, LOOK
	};

public:

	

	//INITIALIZE

	Menu();
	~Menu();
	void init();
	void load();
	//void initShaders();

	//OPENGL
	
	void render();
	void update(int deltaTime);

private:

	void setAnimations();

private:
	Sprite * background, *menu, *sprite;
	Texture spritesheet_background, spritesheet;
	int posyNewGame, time, timeAnimationLeft, timeAnimationRight;
	bool startIsPress;
	bool menuSelected[4];

	void menuSelecteds(int i);
	//Text menu;
};