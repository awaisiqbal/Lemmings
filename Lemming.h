#ifndef _LEMMING_INCLUDE
#define _LEMMING_INCLUDE


#pragma once
#include "Sprite.h"
#include "VariableTexture.h"

class Scene; //forward declaration to avoid circular declaration, in the .ccp we have to include the real header of the scene.h

// Lemming is basically a Sprite that represents one lemming. As such it has
// all properties it needs to track its movement and collisions.
class Lemming
{

public:
	Lemming(Scene* s);
	void init(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram, int i);
	void update(int deltaTime);
	void nextLeftSideAction(int &fall);
	void nextRightSideAction(int &fall);
	void checkFallingStateModifications(int &fall);
	void checkMortalJumpOrWalk();
	void blockRoute();
	void render();
	void changeState(int state);
	glm::vec2 position();
	void setSelected(bool b);
	void setSkill(int skill);
	void setNum(int i);
	void setActive(bool active);
	bool isActive();
	int getState();
	void parachute(bool b);
	void setDigger(bool b);
	bool isDigger();
	void setMapMask(VariableTexture *mapMask);

private:
	void activateSkill();
	bool collision();
	int collisionFloor(int maxFall);
	bool checkExitReached();
	bool hasRightCollision();
	bool hasLeftCollision();
	glm::ivec2 getCurrentCollisionPixels();



private:
	enum LemmingState
	{
		WALKING_LEFT_STATE, WALKING_RIGHT_STATE, FALLING_LEFT_STATE, FALLING_RIGHT_STATE, DIGGING_STATE, FALLING_RIGHT_UMBRELLA_STATE, FALLING_LEFT_UMBRELLA_STATE, BLOCKING_STATE, BASHER_RIGHT_STATE, BASHER_LEFT_STATE, DEAD_BY_JUMP_STATE, WALKING_OUT_STATE, NOT_PLAYING_STATE, BOOM_STATE, CLIMBER_RIGHT_STATE, CLIMBER_LEFT_STATE
	};

	int num;
	LemmingState state;
	Texture spritesheet;
	Sprite *sprite;
	Sprite* spriteSelected;
	Scene* scene;
	VariableTexture *mask;
	bool hasParachuteSkill = false, hasDiggerSkill = false, selected = false, hasBlockerSkill = false, hasBoomSkill = false, hasBasherSkill = false, hasClimberSkill = false;
	bool isActivated = false;
	int skill; // 0 dig, 1 parachute, 2 blocker, 3 bacher, 4 climber,  99 boom
	bool isMortalJump = false;
	glm::vec2 exitDoorPosition;
};


#endif // _LEMMING_INCLUDE


