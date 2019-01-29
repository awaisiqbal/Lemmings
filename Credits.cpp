#include <glm/glm.hpp>
#include "Game.h"
#include <iostream>
#include "Text.h"

#define SPRITE_SIZE_X 64
#define SPRITE_SIZE_Y 64	
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 480

//INITIALIZE

Credits::Credits()
{
}

Credits::~Credits()
{
	if (background != NULL)
	{
		background->free();
		delete background;
		background = NULL;
	}
}

void Credits::setAnimations()
{
}

void Credits::init()
{
	View::init();
	spritesheet_background.loadFromFile("images/menu/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet_background.setMinFilter(GL_NEAREST);
	spritesheet_background.setMagFilter(GL_NEAREST);
	background = Sprite::createSprite(glm::ivec2(607, 447), glm::vec2(1.f, 1.f), &spritesheet_background, &texProgram);
	text.init("fonts/DroidSerif.ttf");
	
}

//OPENGL

void Credits::update(int deltaTime)
{
	exit = false;
	int mouseX = Game::instance().getMousePos().x;
	int mouseY = Game::instance().getMousePos().y;
	if (Game::instance().between(mouseX, mouseY, glm::vec2(19, 404), glm::vec2(167, 422))) {
		exit = true;
		if (Game::instance().getLeftMouse()) {
			Game::instance().changeToMenuState();
		}

	}
}

void Credits::render()
{
	View::render();
	background->render();
	if (exit) text.render("Back to Menu", glm::vec2(20, 420), 22, glm::vec4(1, 1, 0, 30));
	else text.render("Back to Menu", glm::vec2(20, 420), 22, glm::vec4(1, 1, 1, 30));
	
}

void Credits::load()
{
}