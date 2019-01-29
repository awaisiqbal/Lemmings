#include <glm/glm.hpp>
#include "Game.h"
#include <iostream>

#define SPRITE_SIZE_X 64
#define SPRITE_SIZE_Y 64	
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 480

//INITIALIZE

levelSelection::levelSelection()
{
}

levelSelection::~levelSelection()
{
	if (background != NULL)
	{
		background->free();
		delete background;
		background = NULL;
	}
}

void levelSelection::setAnimations()
{
}

void levelSelection::init()
{
	View::init();
	level = 0;
	//max en x, min y, max en y, min x
	spritesheet_background.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet_background.setMinFilter(GL_NEAREST);
	spritesheet_background.setMagFilter(GL_NEAREST);
	background = Sprite::createSprite(glm::ivec2(607, 447), glm::vec2(1.f, 1.f), &spritesheet_background, &texProgram);
	text.init("fonts/DroidSerif.ttf");
}

//OPENGL

void levelSelection::update(int deltaTime)
{
	int mouseX = Game::instance().getMousePos().x;
	int mouseY = Game::instance().getMousePos().y;
	exit = false;
	if (Game::instance().between(mouseX, mouseY, glm::vec2(468, 257), glm::vec2(507, 291))) {
		if (Game::instance().getLeftMouse()) {
			level = 0;
		}
	}
	else if (Game::instance().between(mouseX, mouseY, glm::vec2(468, 305), glm::vec2(509, 350))) {
		if (Game::instance().getLeftMouse()) {
			level = 1;
		}
	}
	else if (Game::instance().between(mouseX, mouseY, glm::vec2(466, 368), glm::vec2(507, 409))) {
		if (Game::instance().getLeftMouse()) {
			level = 2;
		}
	}

	if (Game::instance().between(mouseX, mouseY, glm::vec2(19, 404), glm::vec2(167, 422))) {
		exit = true;
		if (Game::instance().getLeftMouse()) {
			Game::instance().changeToMenuState();
		}
	}
}

void levelSelection::render()
{
	View::render();
	background->render();
	if (exit) text.render("Back to Menu", glm::vec2(20, 420), 22, glm::vec4(1, 1, 0, 30));
	else text.render("Back to Menu", glm::vec2(20, 420), 22, glm::vec4(1, 1, 1, 30));
	text.render("Select Level", glm::vec2(350, 220), 48, glm::vec4(1, 1, 1, 155));
	if(level == 0) text.render("1", glm::vec2(474, 290), 48, glm::vec4(1, 1, 0, 155));
	else text.render("1", glm::vec2(474, 290), 48, glm::vec4(1, 1, 1, 155));
	if (level == 1) text.render("2", glm::vec2(474, 350), 48, glm::vec4(1, 1, 0, 155));
	else text.render("2", glm::vec2(474, 350), 48, glm::vec4(1, 1, 1, 155));
	if (level == 2) text.render("3", glm::vec2(474, 410), 48, glm::vec4(1, 1, 0, 155));
	else text.render("3", glm::vec2(474, 410), 48, glm::vec4(1, 1, 1, 155));
}

void levelSelection::load()
{
}

int levelSelection::getLevel()
{
	return level;
}
