#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>

class View
{

public:

	//INITIALIZE

	View();
	~View();
	void init();
	void render();
	void initShaders();

private:

private:
	glm::mat4 projection;
protected:
	ShaderProgram texProgram;
};