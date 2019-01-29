#include <glm/glm.hpp>
#include "Game.h"
#include <iostream>
#include <vector>

#define SPRITE_SIZE_X 64
#define SPRITE_SIZE_Y 64	
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 480

//INITIALIZE

Instructions::Instructions()
{
}

Instructions::~Instructions()
{
	if (background != NULL)
	{
		background->free();
		delete background;
		background = NULL;
	}

}

void Instructions::setAnimations()
{
}

void Instructions::init()
{
	View::init();	
	spritesheet_background.loadFromFile("images/menu/menuBackground.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet_background.setMinFilter(GL_NEAREST);
	spritesheet_background.setMagFilter(GL_NEAREST); 
	background = Sprite::createSprite(glm::ivec2(607, 447), glm::vec2(1.f, 1.f), &spritesheet_background, &texProgram);
	text.init("fonts/DroidSerif.ttf");
	controls = true;
}

//OPENGL

void Instructions::update(int deltaTime)
{
	int mouseX = Game::instance().getMousePos().x;
	int mouseY = Game::instance().getMousePos().y;
	controls = gameplay = exit = false;
	if (Game::instance().between(mouseX, mouseY, glm::vec2(339, 266), glm::vec2(578,300))) {
		controls = true;
		if (Game::instance().getLeftMouse()) {
			screen = 1;
		}
	}
	else if (Game::instance().between(mouseX, mouseY, glm::vec2(347, 322), glm::vec2(759, 349))) {
		gameplay = true;
		if (Game::instance().getLeftMouse()) {
			screen = 2;
		}
	}
	else if ( Game::instance().between(mouseX, mouseY, glm::vec2(19, 404), glm::vec2(167, 422))) {
		exit = true;
		if (Game::instance().getLeftMouse()) {
			Game::instance().changeToMenuState();
		}

	}
}

void Instructions::render()
{
	View::render();
	background->render();


	if (exit) text.render("Back to Menu", glm::vec2(20, 420), 22, glm::vec4(1, 1, 0, 30));
	else text.render("Back to Menu", glm::vec2(20, 420), 22, glm::vec4(1, 1, 1, 30));
	if (screen == 0) {
		text.render("Instructions", glm::vec2(350, 220), 48, glm::vec4(1, 1, 1, 155));
		if (controls) text.render("HOW TO PLAY", glm::vec2(350, 300), 32, glm::vec4(1, 1, 0, 155));
		else text.render("HOW TO PLAY", glm::vec2(350, 300), 32, glm::vec4(1, 1, 1, 155));
		if (gameplay) text.render("CONTROLS IN GAMEPLAY", glm::vec2(350, 350), 32, glm::vec4(1, 1, 0, 155));
		else text.render("CONTROLS IN GAMEPLAY", glm::vec2(350, 350), 32, glm::vec4(1, 1, 1, 155));		

	}
	else if (screen == 1) {
		text.render("HOW TO PLAY", glm::vec2(330, 220), 48, glm::vec4(1, 1, 1, 155));
		text.render("The objective of the game is to get a certain number of lemmings", glm::vec2(125, 260), 24, glm::vec4(1, 1, 1, 155));
		text.render("to arrive at the exit door from the entrance door, making use ", glm::vec2(125, 300), 24, glm::vec4(1, 1, 1, 155));
		text.render("of the different skills that will be necessary to achieve the goal.", glm::vec2(125, 340), 24, glm::vec4(1, 1, 1, 155));
	}
	else if (screen == 2) {
		text.render("CONTROLS", glm::vec2(330, 220), 48, glm::vec4(1, 1, 1, 155));
		text.render("To select a skill, move the cursor over it in the lower frame of", glm::vec2(125, 260), 24, glm::vec4(1, 1, 1, 155));
		text.render("the screen and left click, then move the cursor over a lemming ", glm::vec2(125, 300), 24, glm::vec4(1, 1, 1, 155));
		text.render("and left click with the mouse to grant the selected lemming the skill.", glm::vec2(125, 340), 24, glm::vec4(1, 1, 1, 155));
	}
	
	
}

void Instructions::load()
{
	screen = 0;
}