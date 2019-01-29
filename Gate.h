#pragma once
#include "VariableTexture.h"
#include "ShaderProgram.h"
#include "Sprite.h"

class Scene; //forward declaration to avoid circular declaration, in the .ccp we have to include the real header of the scene.h

class Gate
{
public:
	Gate(Scene* s);
	~Gate();
	void initEntryGate(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram);
	void initExitGate(const glm::vec2 &initialPosition, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

private:
	enum GateState
	{
		GATE_OPENING_STATE, GATE_OPENED_STATE, EXIT_GATE_STATE
	};

	GateState state;
	Texture spritesheet;
	Sprite *sprite;
	int frames;
	Scene* scene;

};
