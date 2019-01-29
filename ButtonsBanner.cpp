#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "ButtonsBanner.h"
#include "Scene.h"
#include "Game.h"
#include <string>


enum LemmingAnims
{
	ANIM1
};

ButtonsBanner::ButtonsBanner(Scene * s)
{
	scene = s;
	if (scene != NULL) // Used for testing scene
	{
	}
}

void ButtonsBanner::init(const glm::vec2 & initialPosition, ShaderProgram & shaderProgram)
{
	state = STATE_1;
	text.init("fonts/DroidSerif.ttf");
	spritesheet.loadFromFile("images/skills.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(508, 40), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(ANIM1, 12);
	sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.f));
	numToWin = numReachedExitDoor = "0";

	sprite->changeAnimation(ANIM1);
	sprite->setPosition(initialPosition);
}

ButtonsBanner::~ButtonsBanner()
{
}

void ButtonsBanner::update(int deltaTime)
{
	if (sprite->update(deltaTime) == 0)
		return;
	numReachedExitDoor = to_string(Game::instance().getNumLemmingsReachedExitDoor());
	numToWin = to_string(Game::instance().getNumLemmingsToWin());
	minutesLeft = to_string(Game::instance().getMinutesLeft());
	secondsLeft = to_string(Game::instance().getSecondsLeft());
	numLemmingsAlive = to_string(Game::instance().getNumLemmingsAlive());
	switch (state)
	{
	case STATE_1:
		break;

	}
}

void ButtonsBanner::render()
{
	sprite->render();
	text.render("Lemmings To win: ", glm::vec2(695, 391), 16, glm::vec4(0, 1, 0, 255));
	text.render(numReachedExitDoor, glm::vec2(844, 391), 16, glm::vec4(0, 1, 0, 255));
	text.render("/ ", glm::vec2(860, 391), 16, glm::vec4(0, 1, 0, 255));
	text.render(numToWin, glm::vec2(874, 391), 16, glm::vec4(0, 1, 0, 255));
	//TODO falta
	text.render("Time Left: ", glm::vec2(695, 430), 16, glm::vec4(0, 1, 0, 255));
	text.render(minutesLeft, glm::vec2(800, 430), 16, glm::vec4(0, 1, 0, 255));
	text.render(":", glm::vec2(816, 430), 16, glm::vec4(0, 1, 0, 255));
	text.render(secondsLeft, glm::vec2(832, 430), 16, glm::vec4(0, 1, 0, 255));
	//alive
	text.render("Lemmings alive: ", glm::vec2(695, 465), 16, glm::vec4(0, 1, 0, 255));
	text.render(numLemmingsAlive, glm::vec2(844, 465), 18, glm::vec4(0, 1, 0, 255));
	
}

void ButtonsBanner::updatePosition(int mouseX, int mouseY)
{
	glm::vec2 curPos = sprite->position();
	sprite->setPosition(glm::vec2(curPos.x+mouseX,curPos.y + mouseY));
}


void ButtonsBanner::checkSkillSelected(glm::vec2 mouse)
{
	if (Game::instance().between(mouse.x, mouse.y, glm::vec2(7, 382), glm::vec2(96, 479))) { //first skill clicked (parachute)
		scene->selectionMode(1);
	}
	else if (Game::instance().between(mouse.x, mouse.y, glm::vec2(112, 382), glm::vec2(204, 479))) { //second skill clicked (digger)
		scene->selectionMode(0);
	}
	else if (Game::instance().between(mouse.x, mouse.y, glm::vec2(218, 382), glm::vec2(312, 479))) { //third skill clicked (basher)
		scene->selectionMode(3);
	}
	else if (Game::instance().between(mouse.x, mouse.y, glm::vec2(328, 382), glm::vec2(420, 479))) { //fourth skill clicked (blocker)
		scene->selectionMode(2);
	}
	else if (Game::instance().between(mouse.x, mouse.y, glm::vec2(430, 382), glm::vec2(525, 479))) { //fifth skill clicked (climber)
		scene->selectionMode(4);
	}
	else if (Game::instance().between(mouse.x, mouse.y, glm::vec2(533, 382), glm::vec2(628, 479))) { //sixth skill clicked (boom)
		scene->selectionMode(99);
	}
	else if (Game::instance().between(mouse.x, mouse.y, glm::vec2(637, 381), glm::vec2(684, 413))) { //pause game
		scene->pauseScene();
	}
	else if (Game::instance().between(mouse.x, mouse.y, glm::vec2(637, 424), glm::vec2(684, 456))) { //boom all
		scene->deleteAll();
	}
	else if (Game::instance().between(mouse.x, mouse.y, glm::vec2(637, 465), glm::vec2(684, 477))) { //speed
		scene->changeGameVelocity();
	}


}

void ButtonsBanner::checkChangeCursor(glm::vec2 mouse)
{
	bool hab1 = Game::instance().between(mouse.x, mouse.y, glm::vec2(7, 382), glm::vec2(96, 479));
	bool hab2 = Game::instance().between(mouse.x, mouse.y, glm::vec2(112, 382), glm::vec2(204, 479));
	bool hab3 = Game::instance().between(mouse.x, mouse.y, glm::vec2(218, 382), glm::vec2(312, 479));
	bool hab4 = Game::instance().between(mouse.x, mouse.y, glm::vec2(328, 382), glm::vec2(420, 479));
	bool hab5 = Game::instance().between(mouse.x, mouse.y, glm::vec2(430, 382), glm::vec2(525, 479));
	bool hab6 = Game::instance().between(mouse.x, mouse.y, glm::vec2(533, 382), glm::vec2(628, 479));
	bool hab7 = Game::instance().between(mouse.x, mouse.y, glm::vec2(637, 381), glm::vec2(684, 413));
	bool hab8 = Game::instance().between(mouse.x, mouse.y, glm::vec2(637, 424), glm::vec2(684, 456));
	bool hab9 = Game::instance().between(mouse.x, mouse.y, glm::vec2(637, 465), glm::vec2(684, 477));
	if (hab1 || hab2 || hab3 || hab4 || hab5 || hab6 || hab7 || hab8 || hab9)
	{
		scene->setClickableMode(true);
	}
	else {
		scene->setClickableMode(false);
	}
}
