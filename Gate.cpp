#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Gate.h"
#include "Scene.h"
#include "Game.h"


enum GateAnims
{
	GATE_STATE_1, GATE_STATE_2, GATE_EXIT
};

Gate::Gate(Scene* s)
{
	frames = 0;
	scene = s;
}

Gate::~Gate()
{
}

void Gate::initEntryGate(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram)
{
	state = GATE_OPENING_STATE;
	spritesheet.loadFromFile("images/puertaEntrada.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(48, 32), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
	sprite->setAnimationSpeed(GATE_STATE_1, 12);
	for (int i = 0; i < 10; i++)
		sprite->addKeyframe(GATE_STATE_1, glm::vec2(float(i) / 10, 0.0f));

	sprite->setAnimationSpeed(GATE_STATE_2, 2);
	sprite->addKeyframe(GATE_STATE_2, glm::vec2(9.f / 10, 0.0f));
	sprite->changeAnimation(GATE_STATE_1);
	glm::vec2 displacedPos = glm::vec2(initialPosition);
	displacedPos.x -= 18; // sprite displacement to get the middle
	sprite->setPosition(displacedPos);
}

void Gate::initExitGate(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram)
{
	state = EXIT_GATE_STATE;
	spritesheet.loadFromFile("images/puertaSalida.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(40, 32), glm::vec2(0.16666666667, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(GATE_STATE_1, 6);
	for (int i = 0; i < 6; i++)
		sprite->addKeyframe(GATE_STATE_1, glm::vec2(float(i) / 6, 0.0f));
	sprite->changeAnimation(GATE_STATE_1);
	glm::vec2 displacedPos = glm::vec2(initialPosition);
	displacedPos.x -= 20; // sprite displacement to get the middle
	displacedPos.y -= 30; // sprite displacement to get the middle
	sprite->setPosition(displacedPos);
}

void Gate::update(int deltaTime)
{
	if (sprite->update(deltaTime) == 0)
		return;

	switch (state)
	{
	case Gate::GATE_OPENING_STATE:
		if (sprite->getCurrentKeyframe() == 9)
		{
			state = GATE_OPENED_STATE;
			scene->setGateOpened(true);
		}
		break;
	case Gate::GATE_OPENED_STATE:
		if (sprite->animation() != GATE_STATE_2)
		{
			sprite->changeAnimation(GATE_STATE_2);
		}
		break;
	case Gate::EXIT_GATE_STATE:
		break;
	default:
		break;
	}

}

void Gate::render()
{
	sprite->render();
	frames++;
}
