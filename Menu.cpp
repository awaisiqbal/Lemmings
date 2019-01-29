#include <glm/glm.hpp>
#include "Game.h"
#include <iostream>
#include <vector>
#include "SoundSystem.h"

#define SPRITE_SIZE_X 64
#define SPRITE_SIZE_Y 64	
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 480

//INITIALIZE

Menu::Menu()
{
}

Menu::~Menu()
{
	if (background != NULL)
	{
		background->free();
		delete background;
		background = NULL;
	}
}

void Menu::setAnimations()
{
}

void Menu::menuSelecteds(int i)
{
	for (int j = 0; j < 4; ++j) {
		if (j == i) menuSelected[i] = true;
		else menuSelected[j] = false;
	}
}

void Menu::init()
{
	View::init();
	spritesheet_background.loadFromFile("images/menu/mockup.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet_background.setMinFilter(GL_NEAREST);
	spritesheet_background.setMagFilter(GL_NEAREST);
	background = Sprite::createSprite(glm::ivec2(607, 447), glm::vec2(1.f, 1.f), &spritesheet_background, &texProgram);

	spritesheet.loadFromFile("images/flecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &texProgram);
	sprite->setPosition(glm::vec2(11110, 0));
	for (int i = 0; i < 4; i++) menuSelected[i] = false;
	time = 0;
	startIsPress = false;

}

//OPENGL

void Menu::update(int deltaTime)
{
	
	int mouseX = Game::instance().getMousePos().x;
	int mouseY = Game::instance().getMousePos().y;
	if (Game::instance().getLeftMouse()) {
		Game::instance().menuClicked(mouseX, mouseY);
	}
	if (Game::instance().between(mouseX, mouseY, glm::vec2(157, 243), glm::vec2(280, 319))) {
		sprite->setPosition(glm::vec2(70, 245));
		if (!SoundSystem::instance().isPlayingPlay()) SoundSystem::instance().playPlay();
	}
	else if (Game::instance().between(mouseX, mouseY, glm::vec2(599, 252), glm::vec2(875, 303))) {
		sprite->setPosition(glm::vec2(345, 245));
		if (!menuSelected[1]){
			SoundSystem::instance().playButton();
			menuSelecteds(1);
		}
	}
	else if (Game::instance().between(mouseX, mouseY, glm::vec2(273, 325), glm::vec2(444, 368))) {
		sprite->setPosition(glm::vec2(140, 310));
		if (!menuSelected[2]) {
			SoundSystem::instance().playButton();
			menuSelecteds(2);
		}
	}
	else if (Game::instance().between(mouseX, mouseY, glm::vec2(378, 251), glm::vec2(537, 293))){
		sprite->setPosition(glm::vec2(205, 245));
		if (!menuSelected[0]) {
			SoundSystem::instance().playButton();
			menuSelecteds(0);
		}
	}
	else if (Game::instance().between(mouseX, mouseY, glm::vec2(495, 333), glm::vec2(610, 371))) {
		sprite->setPosition(glm::vec2(285, 313));
		if (!menuSelected[3]) {
			SoundSystem::instance().playButton(); 
			menuSelecteds(3);

		}
	}
	else sprite->setPosition(glm::vec2(10000, 0));
	
	
}

void Menu::render()
{
	View::render();
	background->render();
	sprite->render();
}

void Menu::load()
{
	if(!SoundSystem::instance().isPlayingBackground())SoundSystem::instance().playBackground();
	time = timeAnimationLeft = 0;
	startIsPress = false;
}
