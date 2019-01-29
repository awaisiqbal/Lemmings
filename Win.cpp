#include <glm/glm.hpp>
#include "Win.h"
#include "Game.h"
#include <iostream>

#define SPRITE_SIZE_X 64
#define SPRITE_SIZE_Y 64	
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 480

//INITIALIZE

Win::Win()
{
}

Win::~Win()
{
}

void Win::init()
{
	View::init();
	spritesheet_background.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet_background.setMinFilter(GL_NEAREST);
	spritesheet_background.setMagFilter(GL_NEAREST);
	background = Sprite::createSprite(glm::ivec2(607, 447), glm::vec2(1.f, 1.f), &spritesheet_background, &texProgram);
	text.init("fonts/DroidSerif.ttf");
}

//OPENGL

void Win::update(int deltaTime)
{
	int mouseX = Game::instance().getMousePos().x;
	int mouseY = Game::instance().getMousePos().y;
	exit = false;
	if (Game::instance().between(mouseX, mouseY, glm::vec2(19, 404), glm::vec2(167, 422))) {
		exit = true;
		if (Game::instance().getLeftMouse()) {
			SoundSystem::instance().restartSound();
			Game::instance().changeToMenuState();
		}
	}
 	
}

void Win::render()
{
	View::render();
	background->render();
	if (exit) text.render("Back to Menu", glm::vec2(20, 420), 22, glm::vec4(1, 1, 0, 30));
	else text.render("Back to Menu", glm::vec2(20, 420), 22, glm::vec4(1, 1, 1, 30));
	text.render("YOU WIN", glm::vec2(350, 300), 32, glm::vec4(1, 1, 0, 155));
}

void Win::load()
{
}
