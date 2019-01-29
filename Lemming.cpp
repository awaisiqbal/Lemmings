#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Lemming.h"
#include "Scene.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define posCameraX 0
#define posCameraY 0


enum LemmingAnims
{
	WALKING_LEFT, WALKING_RIGHT, FALLING_RIGHT, FALLING_LEFT, DIGGING, FALLING_RIGHT_UMBRELLA, FALLING_LEFT_UMBRELLA, WALKING_RIGHT_UMBRELLA, WALKING_LEFT_UMBRELLA, BLOCKER, BASHER_RIGHT, BASHER_LEFT, EXITING_GAME, DEAD_BY_JUMP, BOOM, CLIMBER_RIGHT, CLIMBER_LEFT
};

Lemming::Lemming(Scene* s)
{
	scene = s;
	if (scene != NULL) // Used for testing scene
	{
	}

}

void Lemming::init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, int i)
{
	num = i;
	skill = -1;
	exitDoorPosition = scene->getExitDoorPos();
	state = FALLING_RIGHT_STATE;
	hasDiggerSkill = hasParachuteSkill = hasBoomSkill = hasBlockerSkill = false;
	selected = false;
	spritesheet.loadFromFile("images/lemming_extendido.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.125, 0.0625), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(17);

	sprite->setAnimationSpeed(WALKING_RIGHT, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(WALKING_RIGHT, glm::vec2(float(i) / 8, 0.0f));

	sprite->setAnimationSpeed(WALKING_LEFT, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(WALKING_LEFT, glm::vec2(float(i) / 8, 0.0625f));

	sprite->setAnimationSpeed(FALLING_RIGHT, 12);
	for (int i = 0; i < 4; i++)
		sprite->addKeyframe(FALLING_RIGHT, glm::vec2(float(i) / 8, 0.125f));

	sprite->setAnimationSpeed(FALLING_LEFT, 12);
	for (int i = 0; i < 4; i++)
		sprite->addKeyframe(FALLING_LEFT, glm::vec2(float(i + 4) / 8, 0.125f));

	sprite->setAnimationSpeed(DIGGING, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(DIGGING, glm::vec2(float(i) / 8, 0.1875f));

	sprite->setAnimationSpeed(FALLING_RIGHT_UMBRELLA, 12);
	sprite->addKeyframe(FALLING_RIGHT_UMBRELLA, glm::vec2(0.0f / 8.f, 0.25f));

	sprite->setAnimationSpeed(FALLING_LEFT_UMBRELLA, 12);
	sprite->addKeyframe(FALLING_LEFT_UMBRELLA, glm::vec2(1.0f / 8.f, 0.25f));

	sprite->setAnimationSpeed(WALKING_RIGHT_UMBRELLA, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(WALKING_RIGHT_UMBRELLA, glm::vec2(float(i) / 8, 0.3125f));

	sprite->setAnimationSpeed(WALKING_LEFT_UMBRELLA, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(WALKING_LEFT_UMBRELLA, glm::vec2(float(i) / 8, 0.375f));

	sprite->setAnimationSpeed(BLOCKER, 6);
	for (int i = 2; i < 6; i++)
		sprite->addKeyframe(BLOCKER, glm::vec2(float(i)/8, 0.25f));
	

	sprite->setAnimationSpeed(EXITING_GAME, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(EXITING_GAME, glm::vec2(float(i) / 8, 0.625f));

	sprite->setAnimationSpeed(DEAD_BY_JUMP, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(DEAD_BY_JUMP, glm::vec2(float(i) / 8, 0.5f));

	sprite->setAnimationSpeed(BASHER_RIGHT, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(BASHER_RIGHT, glm::vec2(float(i) / 8, 0.5625f));

	sprite->setAnimationSpeed(BOOM, 6);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(BOOM, glm::vec2(float(i) / 8, 0.4375f));

	sprite->setAnimationSpeed(CLIMBER_RIGHT, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(CLIMBER_RIGHT, glm::vec2(float(i) / 8, 0.6875f));

	sprite->setAnimationSpeed(CLIMBER_LEFT, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(CLIMBER_LEFT, glm::vec2(float(i) / 8, 0.75f));

	sprite->setAnimationSpeed(BASHER_LEFT, 12);
	for (int i = 0; i < 8; i++)
		sprite->addKeyframe(BASHER_LEFT, glm::vec2(float(i) / 8, 0.8125f));

	sprite->changeAnimation(FALLING_RIGHT); //PARA PROBAR SPRITE DIGGING
	sprite->setPosition(initialPosition);
}

void Lemming::update(int deltaTime)
{
	if ((!isActivated) || sprite->update(deltaTime) == 0)
		return; //when lemming is not activated or sprite is not updated

	if (selected) activateSkill();//if the lemming is selected then activate the skills
	if (hasBoomSkill)	//Lemming should explode
	{
		state = BOOM_STATE;
	}
	if (state != NOT_PLAYING_STATE && state != WALKING_OUT_STATE && checkExitReached()) // when the lemming is just arrived for first time to the exit door
	{
		state = WALKING_OUT_STATE;
		sprite->changeAnimation(EXITING_GAME);
	}
	glm::ivec2 posBase = getCurrentCollisionPixels();
	int fall;
	switch (state)
	{
	case FALLING_LEFT_STATE:
		if (hasParachuteSkill) {
			isMortalJump = false;
			sprite->changeAnimation(FALLING_LEFT_UMBRELLA);
			state = FALLING_LEFT_UMBRELLA_STATE;
		}
		checkFallingStateModifications(fall);
		break;

	case FALLING_RIGHT_STATE:
		if (hasParachuteSkill) {
			isMortalJump = false;
			sprite->changeAnimation(FALLING_RIGHT_UMBRELLA);
			state = FALLING_RIGHT_UMBRELLA_STATE;
		}
		checkFallingStateModifications(fall);
		break;

	case WALKING_LEFT_STATE:
		if (hasParachuteSkill && sprite->animation() != WALKING_LEFT_UMBRELLA && !hasDiggerSkill) sprite->changeAnimation(WALKING_LEFT_UMBRELLA);
		else if (!hasParachuteSkill && sprite->animation() != WALKING_LEFT && !hasDiggerSkill) sprite->changeAnimation(WALKING_LEFT);

		if (hasDiggerSkill) {
			state = DIGGING_STATE;
		}
		else if (hasBlockerSkill) blockRoute();
		else {
			sprite->position() += glm::vec2(-1, -1);
			if (collision())
			{
				sprite->position() -= glm::vec2(-1, -1);
				if (hasBasherSkill) {
					if (sprite->animation() != BASHER_LEFT) sprite->changeAnimation(BASHER_LEFT);
					state = BASHER_LEFT_STATE;
				}
				else if (hasClimberSkill) {
					if (sprite->animation() != CLIMBER_LEFT) sprite->changeAnimation(CLIMBER_LEFT);
					state = CLIMBER_LEFT_STATE;
				}
				else {
					sprite->changeAnimation(WALKING_RIGHT);
					state = WALKING_RIGHT_STATE;
				}

				
			}
			else
			{
				nextLeftSideAction(fall);
			}
		}
		break;

	case WALKING_RIGHT_STATE:
		if (hasDiggerSkill) {
			state = DIGGING_STATE;
		}
		else if (hasBlockerSkill)	blockRoute();
		else {
			sprite->position() += glm::vec2(1, -1);
			if (collision())
			{
				sprite->position() -= glm::vec2(1, -1); // when collision happens return to the initial pos
				if (hasBasherSkill) {
					if (sprite->animation() != BASHER_RIGHT) sprite->changeAnimation(BASHER_RIGHT);
					state = BASHER_RIGHT_STATE;
				}
				else if (hasClimberSkill){
					if (sprite->animation() != CLIMBER_RIGHT) sprite->changeAnimation(CLIMBER_RIGHT);
					state = CLIMBER_RIGHT_STATE;
				}
				else {
					sprite->changeAnimation(WALKING_LEFT);
					state = WALKING_LEFT_STATE;
				}
			}
			else
			{
				nextRightSideAction(fall);
			}
		}
		break;

	case DIGGING_STATE:
		if (sprite->animation() != DIGGING) sprite->changeAnimation(DIGGING);
		scene->eraseMask(glm::ivec2(sprite->position() + glm::vec2(posCameraX, posCameraY) + glm::vec2(7, 13)));
		sprite->position() += glm::vec2(0, 1);
		fall = collisionFloor(2);
		if (mask->pixel(posBase.x, posBase.y + 2) == NON_BLOCKING_PIXEL)
		{
			hasDiggerSkill = false;
			nextRightSideAction(fall);
		}
		break;

	case FALLING_RIGHT_UMBRELLA_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			sprite->position() += glm::vec2(0, fall);
		else {
			state = WALKING_RIGHT_STATE;
			sprite->changeAnimation(WALKING_RIGHT);
		}
		break;

	case FALLING_LEFT_UMBRELLA_STATE:
		fall = collisionFloor(2);
		if (fall > 0)
			sprite->position() += glm::vec2(0, fall);
		else {
			state = WALKING_LEFT_STATE;
			sprite->changeAnimation(WALKING_LEFT);
		}
		break;
	case BASHER_RIGHT_STATE:
		cout << "BASHER" << endl;
		sprite->position() += glm::vec2(1, 0);
		for (int i = 0; i < 8; i++)
		{
			int x = posBase.x + 1;
			int y = posBase.y - i;
			scene->eraseMaskPixel(x, y);
		}

		if (!hasRightCollision()) {
			nextRightSideAction(fall);
		}
		break;

	case BASHER_LEFT_STATE:
		cout << "BASHER" << endl;
		sprite->position() += glm::vec2(-1, 0);
		for (int i = 0; i < 8; i++)
		{
			int x = posBase.x - 1;
			int y = posBase.y - i;
			scene->eraseMaskPixel(x, y);
		}

		if (!hasLeftCollision()) {
			nextLeftSideAction(fall);
		}
		break;

	case CLIMBER_RIGHT_STATE:
		sprite->position() += glm::vec2(0, -1);
		if (!hasRightCollision()) {
			sprite->position() += glm::vec2(1, 0);
			nextRightSideAction(fall);
		}
		break;

	case CLIMBER_LEFT_STATE:
		sprite->position() += glm::vec2(0, -1);
		if (!hasLeftCollision()) {
			sprite->position() += glm::vec2(-1, 0);
			nextLeftSideAction(fall);
		}
		break;

	case BLOCKING_STATE:

		break;

	case DEAD_BY_JUMP_STATE:
		if (sprite->getCurrentKeyframe() == 7)
		{
			state = NOT_PLAYING_STATE;
			scene->lemmingDeath(num);
		}
		break;

	case WALKING_OUT_STATE:
		if(sprite->animation() != EXITING_GAME) sprite->changeAnimation(EXITING_GAME);
		if (sprite->getCurrentKeyframe() == 7)
		{
			state = NOT_PLAYING_STATE;
			//scene->lemmingReachedExit(num);
		}
		break;
	case BOOM_STATE:
		if (sprite->animation() != BOOM) sprite->changeAnimation(BOOM);
		if (sprite->getCurrentKeyframe() == 7) {
			scene->eraseMaskCircle(glm::ivec2(sprite->position() + glm::vec2(posCameraX, posCameraY) + glm::vec2(7, 7)));
			state = NOT_PLAYING_STATE;
			scene->lemmingDeath(num);
		}
		break;

	case NOT_PLAYING_STATE:
		if (isActivated) {
			scene->lemmingReachedExit(num);
		}
		break;


	}
	selected = false;
}

void Lemming::nextLeftSideAction(int &fall)
{
	fall = collisionFloor(3);
	if (fall < 3) {
		sprite->position() += glm::vec2(0, fall);
		if (fall == 0 || fall == 1) {
			if (hasParachuteSkill && sprite->animation() != WALKING_LEFT_UMBRELLA && !hasDiggerSkill) sprite->changeAnimation(WALKING_LEFT_UMBRELLA);
			else if (!hasParachuteSkill && sprite->animation() != WALKING_LEFT && !hasDiggerSkill) sprite->changeAnimation(WALKING_LEFT);
			state = WALKING_LEFT_STATE;
		}
		else {
			state = FALLING_LEFT_UMBRELLA_STATE;
		}
	}
	else if (hasParachuteSkill) {
		state = FALLING_LEFT_UMBRELLA_STATE;
		sprite->changeAnimation(FALLING_LEFT_UMBRELLA);
	}
	else {
		state = FALLING_LEFT_STATE;
		sprite->changeAnimation(FALLING_LEFT);
	}
}

void Lemming::nextRightSideAction(int &fall)
{
	fall = collisionFloor(3);
	if (fall < 3) {
		sprite->position() += glm::vec2(0, fall);
		if (fall == 0 || fall == 1) {
			if (hasParachuteSkill && sprite->animation() != WALKING_RIGHT_UMBRELLA && !hasDiggerSkill) sprite->changeAnimation(WALKING_RIGHT_UMBRELLA);
			else if (!hasParachuteSkill && sprite->animation() != WALKING_RIGHT && !hasDiggerSkill) sprite->changeAnimation(WALKING_RIGHT);
			state = WALKING_RIGHT_STATE;
		}
		else {
			state = FALLING_RIGHT_UMBRELLA_STATE;
		}
	}
	else if (hasParachuteSkill) {
		state = FALLING_RIGHT_UMBRELLA_STATE;
		sprite->changeAnimation(FALLING_RIGHT_UMBRELLA);
	}
	else {
		state = FALLING_RIGHT_STATE;
		sprite->changeAnimation(FALLING_RIGHT);
	}
}

void Lemming::checkFallingStateModifications(int &fall)
{
	fall = collisionFloor(2);
	if (fall > 0) {
		sprite->position() += glm::vec2(0, fall);
		if (!isMortalJump && collisionFloor(35) > 30 && !hasParachuteSkill) {
			cout << "IS MORTAL JUMP" << endl;
			isMortalJump = true;
		}
	}
	else {
		checkMortalJumpOrWalk();
	}
}

void Lemming::checkMortalJumpOrWalk()
{
	if (isMortalJump) {
		cout << " Mortal LANDING" << endl;
		state = DEAD_BY_JUMP_STATE;
		//TODO BORRAR LEMMING
		sprite->changeAnimation(DEAD_BY_JUMP);
	}
	else {
		if (state == FALLING_LEFT_STATE) {
			state = WALKING_LEFT_STATE;
			sprite->changeAnimation(WALKING_LEFT);
		}
		else if (state == FALLING_RIGHT_STATE) {
			state = WALKING_RIGHT_STATE;
			sprite->changeAnimation(WALKING_RIGHT);
		}
	}
}

void Lemming::blockRoute()
{
	if (sprite->animation() != BLOCKER) sprite->changeAnimation(BLOCKER);
	state = BLOCKING_STATE;
	glm::ivec2 venterToBlock = sprite->position() + glm::vec2(posCameraX, posCameraY) + glm::vec2(7, 7);
	scene->applyMaskLEM(venterToBlock.x, venterToBlock.y);
}

void Lemming::render()
{
	if (!isActivated) return;
	sprite->render();
}

void Lemming::activateSkill()
{
	hasDiggerSkill = false;
	hasParachuteSkill = false;
	hasBoomSkill = false;
	hasBasherSkill = false;
	hasClimberSkill = false;

	if (skill == 0) { //DIG
		hasDiggerSkill = true;
	}
	else if (skill == 1) {	//PARACHUTE
		hasParachuteSkill = true;
		isMortalJump = false; //Important to avoid dead when falling and put parachute
	}
	else if (skill == 2) {	//BLOCKER
		hasBlockerSkill = true;
	}
	else if (skill == 3) {	//BACHER
		hasBasherSkill = true;
	}
	else if (skill == 4) {	//CLIMBER
		hasClimberSkill = true;
	}
	else if (skill == 99) {	//BOOM
		hasBoomSkill = true;
	}
	selected = false;
}

void Lemming::changeState(int state)
{
	if (state == 4) {
		this->state = WALKING_LEFT_STATE;
		sprite->changeAnimation(WALKING_LEFT);
	}
	else {
		this->state = WALKING_RIGHT_STATE;
		sprite->changeAnimation(WALKING_RIGHT);
	}
}

bool Lemming::collision()
{
	glm::ivec2 posBase = sprite->position() + glm::vec2(posCameraX, posCameraY); // Add the map displacement
	posBase += glm::ivec2(7, 15);
	//std::cout << "checking collision: " << posBase.x << " , " << posBase.y << std::endl;
	if ((mask->pixel(posBase.x, posBase.y) == NON_BLOCKING_PIXEL) && (mask->pixel(posBase.x + 1, posBase.y) == NON_BLOCKING_PIXEL))
		return false;

	return true;
}

int Lemming::collisionFloor(int maxFall)
{
	bool bContact = false;
	int fall = 0;
	glm::ivec2 posBase = sprite->position() + glm::vec2(posCameraX, posCameraY); // Add the map displacement

	posBase += glm::ivec2(7, 16); // calculate the sprite middle and center pos
	while ((fall < maxFall) && !bContact)
	{
		if ((mask->pixel(posBase.x, posBase.y + fall) == NON_BLOCKING_PIXEL) && (mask->pixel(posBase.x + 1, posBase.y + fall) == NON_BLOCKING_PIXEL))
			fall += 1;
		else
			bContact = true;
	}

	return fall;
}

bool Lemming::checkExitReached()
{
	glm::ivec2 posBase = sprite->position() + glm::vec2(posCameraX, posCameraY); // Add the map displacement

	posBase += glm::ivec2(7, 15);
	if ((posBase.x == exitDoorPosition.x) && (posBase.y == exitDoorPosition.y))
	{
		
		return true;
	}


	return false;
}

bool Lemming::hasRightCollision()
{
	bool hasCollision = false;
	sprite->position() += glm::vec2(1, -1);
	if (collision()) {
		hasCollision = true;
	}
	sprite->position() -= glm::vec2(1, -1);
	return hasCollision;
}

bool Lemming::hasLeftCollision()
{
	bool hasCollision = false;
	sprite->position() += glm::vec2(-1, -1);
	if (collision()) {
		hasCollision = true;
	}
	sprite->position() -= glm::vec2(-1, -1);
	return hasCollision;
}

glm::ivec2 Lemming::getCurrentCollisionPixels()
{
	glm::ivec2 posBase = sprite->position() + glm::vec2(posCameraX, posCameraY); // Add the map displacement
	posBase += glm::ivec2(7, 15);
	return posBase;
}

glm::vec2 Lemming::position()
{
	return sprite->position() + glm::vec2(posCameraX, posCameraY) + glm::vec2(7, 7);
}

void Lemming::setSelected(bool b)
{
	selected = b;
}

void Lemming::setSkill(int skill)

{
	this->skill = skill;
}

void Lemming::setNum(int i)
{
	num = i;
}

void Lemming::setActive(bool active)
{
	isActivated = active;
}

bool Lemming::isActive()
{
	return isActivated;
}

int Lemming::getState()
{
	return state;
}

void Lemming::parachute(bool b)
{
	hasParachuteSkill = b;

}

void Lemming::setDigger(bool b)

{
	this->hasDiggerSkill = b;
}

bool Lemming::isDigger()
{
	return hasDiggerSkill;
}

void Lemming::setMapMask(VariableTexture *mapMask)
{
	mask = mapMask;
}