#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "SoundSystem.h"
#include "Game.h"

using namespace glm;
using namespace std;

Scene::Scene()
{
	map = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
}

void Scene::initVariables()
{
	initVariablesLevel();


	//INIT LEVELS
	//LEVEL1
	levelCameraInitialPos[0] = glm::vec2(0.f, 5.f);
	levelLemmingsInitPos[0] = glm::vec2(180, 36);
	//levelLemmingsInitPos[0] = glm::vec2(0, 0); //testing
	levelLemmingsExitPos[0] = glm::vec2(355, 130);
	mapRoute[0] = "images/fun1.png";
	maskRoute[0] = "images/fun1_mask.png";
	mapSpriteUtilPixels[0] = vec2(512.f, 160.f);
	mapSpriteDimensions[0] = vec2(512.f, 256.f);



	//LEVEL2
	levelCameraInitialPos[1] = glm::vec2(0.f, 5.f);
	levelLemmingsInitPos[1] = glm::vec2(180, 36);
	//levelLemmingsInitPos[1] = glm::vec2(0, 0); //testing
	levelLemmingsExitPos[1] = glm::vec2(390, 171);
	mapRoute[1] = "images/fun2.png";
	maskRoute[1] = "images/fun2_mask.png";
	mapSpriteUtilPixels[1] = vec2(512.f, 186.f);
	mapSpriteDimensions[1] = vec2(512.f, 256.f);



	//LEVEL3
	levelCameraInitialPos[2] = glm::vec2(0.f, 5.f);
	levelLemmingsInitPos[2] = glm::vec2(180, 8);
	//levelLemmingsInitPos[0] = glm::vec2(0, 0); //testing
	levelLemmingsExitPos[2] = glm::vec2(345, 178);
	mapRoute[2] = "images/fun3.png";
	maskRoute[2] = "images/fun3_mask.png";
	mapSpriteUtilPixels[2] = vec2(512.f, 186.f);
	mapSpriteDimensions[2] = vec2(512.f, 256.f);


}

void Scene::initVariablesLevel()
{
	lemmingActivated = false;
	maxTime = 90000.0f;
	currentTime = 0.0f;
	cameraDimensions = glm::vec2(480, 160);
	numLemmingActives = numLemmingsActivated = numLemmingsReachedExitDoor = 0;//number of lemmings actives
	numTotalLemmings = 10;
	numLemmingsToWin = 3;
	numLemmingsDead = 0;
	velocityMultiplier = 5;
	timeBetweenLemmings = 2000;
	cameraLeft = 0.f;
	cameraRight = cameraDimensions.x;
	cameraBottom = cameraDimensions.y;
	cameraTop = 0.f;
}

void Scene::init()
{
	cout << "Init Scene!" << endl;
	initVariables();

	initShaders();
}

void Scene::initGates()
{
	entryGate = new Gate(this);
	vec2 gateSpritePos = vec2(levelLemmingsInitPos[currentLevel].x, levelLemmingsInitPos[currentLevel].y);
	entryGate->initEntryGate(gateSpritePos, simpleTexProgram);

	exitGate = new Gate(this);
	vec2 gateSpritePosEx = vec2(levelLemmingsExitPos[currentLevel].x, levelLemmingsExitPos[currentLevel].y);
	exitGate->initExitGate(gateSpritePosEx, simpleTexProgram);
}

void Scene::initBanner()
{
	banner = new ButtonsBanner(this);
	vec2 bannerSpritePos = vec2(0, 125);
	banner->init(bannerSpritePos, simpleTexProgram);
}

void Scene::initLemmings()
{
	lemmings.clear();
	for (int i = 0; i < numTotalLemmings; i++)
	{
		lemmings.push_back(new Lemming(this));
		lemmings[i]->init(levelLemmingsInitPos[currentLevel], simpleTexProgram, i);
		lemmings[i]->setMapMask(&maskTexture);
	}
}

void Scene::loadLevel(int level) {
	currentLevel = level;
	SoundSystem::instance().playScene(level);
	initVariablesLevel();

	initCameraAndTexture();

	initGates();

	initBanner();

	initLemmings();
}


void Scene::initCameraAndTexture()
{
	loadMapQuadAndTexture();

	moveCamera(0.f, 0.f, 0.f, 0.f);// just to start projection

}

/* METHOD TO MOVE CAMERA, GIVING PIXELS TO MOVE IN THAT DIRECTION */
void Scene::moveCamera(float left, float right, float bottom, float top)
{
	if (left != 0.f && cameraLeft - left >= 0.f)
	{
		cameraLeft -= left;
		cameraRight -= left;
		banner->updatePosition(-5, 0);
	}
	if (right != 0.f && cameraRight + right < mapSpriteUtilPixels[currentLevel].x)
	{
		cameraLeft += right;
		cameraRight += right;
		banner->updatePosition(5, 0);
	}
	if (bottom != 0.f && cameraBottom + bottom < mapSpriteUtilPixels[currentLevel].y+30)
	{
		cameraBottom += bottom;
		cameraTop += bottom;
		banner->updatePosition(0, 5);
	}
	if (top != 0.f && cameraTop - top >= 0.f)
	{
		cameraBottom -= top;
		cameraTop -= top;
		banner->updatePosition(0, -5);
	}
	updateCamera();
}

/* UPDATE PROJECTION MATRIX */
void Scene::updateCamera()
{
	projection = glm::ortho(cameraLeft, cameraRight, cameraBottom, cameraTop);
}

/* LOAD MAP QUAD AND TEXTURE */
void Scene::loadMapQuadAndTexture()
{
	vec2 quadSize[2] = { vec2(0.f, 0.f), vec2(mapSpriteUtilPixels[currentLevel].x,mapSpriteUtilPixels[currentLevel].y) };

	vec2 partToLoad = vec2(mapSpriteUtilPixels[currentLevel].x / mapSpriteDimensions[currentLevel].x,
		mapSpriteUtilPixels[currentLevel].y / mapSpriteDimensions[currentLevel].y);
	vec2 spritePartToLoad[2] = { vec2(0.f,0.f) , partToLoad }; // indicate to load all the sprite

	map = MaskedTexturedQuad::createTexturedQuad(quadSize, spritePartToLoad, maskedTexProgram);
	colorTexture.loadFromFile(mapRoute[currentLevel], TEXTURE_PIXEL_FORMAT_RGBA);
	colorTexture.setMinFilter(GL_NEAREST);
	colorTexture.setMagFilter(GL_NEAREST);
	maskTexture.loadFromFile(maskRoute[currentLevel], TEXTURE_PIXEL_FORMAT_L);
	maskTexture.setMinFilter(GL_NEAREST);
	maskTexture.setMagFilter(GL_NEAREST);
}

/* METHOD CALLED FROM GAME */
void Scene::updateThisScene(int deltaTime)
{
	SoundSystem::instance().updateSoundSystem();
	//std::cout << numLemmingActivos << endl;
	maxTime -= deltaTime;
	//cout << maxTime << endl;
	if (maxTime <= 0.0f) {
		deleteAll();
		Game::instance().changeToLoseState();
	}
	if (isDoubleVelocity)
		deltaTime = deltaTime * velocityMultiplier;

	if (!isPaused)
		updateThisSceneElements(deltaTime);

	if (isTestDig) {
		for (int i = 0; i < numLemmingsActivated; i++)
		{
			//lemmings[i]->changeState(DIGGING_STATE);
			lemmings[i]->setDigger(true);
		}
	}
	/*else {
		for (int i = 0; i < numLemmingsActivated; i++)
		{
			//if (lemmings[i]->getState() == 4) lemmings[i]->changeState(WALKING_LEFT_STATE);
			if (lemmings[i]->isDigger()) lemmings[i]->setDigger(false);
		}
	}*/

	if (isTestParachute) {
		for (int i = 0; i < numLemmingsActivated; i++)
		{
			lemmings[i]->parachute(true);
		}
	}
	/*else {
		for (int i = 0; i < numLemmingsActivated; i++)
		{
			lemmings[i]->parachute(false);
		}
	}*/
	if (isClickableMode) {
		glutSetCursor(GLUT_CURSOR_INFO);
	}
	else {
		if (isSelectionMode) {
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		}
		else {
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		}
	}
	

	//COMPROBAR SI HAS GANADO int numLemmingActives, numLemmingsActivated, numLemmingsReachedExitDoor, numTotalLemmings;
	if (numLemmingsReachedExitDoor == numLemmingsToWin) {
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		Game::instance().changeToWinState();
	}
	if ((numTotalLemmings - (numLemmingsActivated - numLemmingActives) < numLemmingsToWin)) {
		/*cout << "total: " << numTotalLemmings << endl;
		cout << "activated: " << numLemmingsActivated << endl;
		cout << "activos: " << numLemmingActives << endl;*/
		deleteAll();
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		Game::instance().changeToLoseState();
		
	}
}

/* UPDATE ALL THE ELEMENTS ON THE SCENE */
void Scene::updateThisSceneElements(int deltaTime)
{
	currentTime += deltaTime;
	entryGate->update(deltaTime);
	exitGate->update(deltaTime);
	banner->update(deltaTime);
	//TODO mirar hay que aplicar otra formula para que no salgan todos los lemmings pegados
	bool checkSimpleVelocity = !isDoubleVelocity && ((currentTime - timeLastLemming >= timeBetweenLemmings || timeLastLemming == 0) && numLemmingsActivated < numTotalLemmings);
	bool checkFastVelocity = (currentTime - timeLastLemming >= timeBetweenLemmings * 2 || timeLastLemming == 0) && numLemmingsActivated < numTotalLemmings;
	if ((checkSimpleVelocity || checkFastVelocity) && isGateOpened) {
		lemmings[numLemmingsActivated]->setActive(true);
		++numLemmingActives;
		++numLemmingsActivated;
		if (!lemmingActivated) lemmingActivated = true;
		timeLastLemming = currentTime;
	}
	for (int i = 0; i < numLemmingsActivated; i++)
	{
		lemmings[i]->update(deltaTime);
	}

}

void Scene::render()
{
	glm::mat4 modelview;
	checkCameraMove();
	maskedTexProgram.use();
	maskedTexProgram.setUniformMatrix4f("projection", projection);
	maskedTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	maskedTexProgram.setUniformMatrix4f("modelview", modelview);
	map->render(maskedTexProgram, colorTexture, maskTexture);

	simpleTexProgram.use();
	simpleTexProgram.setUniformMatrix4f("projection", projection);
	simpleTexProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	simpleTexProgram.setUniformMatrix4f("modelview", modelview);

	entryGate->render();
	exitGate->render();

	for (int i = 0; i < numLemmingsActivated; i++)
	{
		lemmings[i]->render();
	}

	banner->render();

}

void Scene::mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton)
{
	if (bLeftButton)
	{
		cout << "Click en: " << calculateMouseToMapCoord(mouseX, mouseY).x << " , " << calculateMouseToMapCoord(mouseX, mouseY).y << endl;
		banner->checkSkillSelected(glm::vec2 (mouseX,mouseY));
	}

	if (isSelectionMode && bLeftButton) {
		selectLemming(mouseX, mouseY, skill);
	}
	banner->checkChangeCursor(glm::vec2(mouseX, mouseY));
	/*
	if (!isSelectionMode && bLeftButton) {
		eraseMask(mouseX, mouseY);
	}
	else if (isSelectionMode && bLeftButton) {
		selectLemming(mouseX, mouseY, skill);
	}
	else if (bRightButton)
		applyMask(mouseX, mouseY);*/
	manageScrolling(mouseX, mouseY);
}

/* CHECK IF WE SHOULD SCROLL */
void Scene::manageScrolling(int mouseX, int mouseY)
{
	isScrollingLeft = mouseX <= WINDOWS_LEFT_SCROLLING_MARGIN;
	isScrollingRight = mouseX >= WINDOWS_RIGHT_SCROLLING_MARGIN;
	isScrollingTop = mouseY <= WINDOWS_TOP_SCROLLING_MARGIN;
	isScrollingBottom = mouseY >= WINDOWS_BOTTOM_SCROLLING_MARGIN;
	/*if (isScrollingLeft)
		cout << "X <= 60" << endl;
	if (isScrollingRight)
		cout << "X > 900" << endl;
	if (isScrollingTop)
		cout << "Y <= 60" << endl;
	if (isScrollingBottom)
		cout << "Y > 420" << endl;*/
}

/* CHECK IF THE CAMERA SHOULD MOVE */
void Scene::checkCameraMove() {
	if (isScrollingLeft)
	{
		moveCamera(5.f, 0.f, 0.f, 0.f);
		
	}
	if (isScrollingRight)
	{
		moveCamera(0.f, 5.f, 0.f, 0.f);
		
	}
	if (isScrollingBottom)
	{
		moveCamera(0.f, 0.f, 5.f, 0.f);
		
	}
	else if (isScrollingTop)
	{
		moveCamera(0.f, 0.f, 0.f, 5.f);
		
	}
}

void Scene::pauseScene()
{
	isPaused = !isPaused;
}

void Scene::changeGameVelocity()
{
	isDoubleVelocity = !isDoubleVelocity;
}

vec2 Scene::calculateMouseToMapCoord(int mouseX, int mouseY)
{
	return vec2(mouseX / (WINDOWS_WIDTH / cameraDimensions.x) + cameraRight - cameraDimensions.x, mouseY / (WINDOWS_HEIGHT / cameraDimensions.y) + cameraBottom - cameraDimensions.y);
}

void Scene::eraseMask(int mouseX, int mouseY)
{
	vec2 pos = calculateMouseToMapCoord(mouseX, mouseY);
	for (int y = glm::max(0, (int)pos.y - 3); y <= glm::min(maskTexture.height() - 1, (int)pos.y + 3); y++)
		for (int x = glm::max(0, (int)pos.x - 3); x <= glm::min(maskTexture.width() - 1, (int)pos.x + 3); x++)
			maskTexture.setPixel(x, y, NON_BLOCKING_PIXEL);
}

void Scene::eraseMaskPixel(int posX, int posY)
{
	maskTexture.setPixel(posX, posY, NON_BLOCKING_PIXEL);
}

void Scene::eraseMaskDigging(int mouseX, int mouseY)
{
	int posX, posY;

	posX = mouseX;
	posY = mouseY;
	for (int y = glm::max(0, posY - 3); y <= glm::min(maskTexture.height() - 1, posY + 3); y++)
		for (int x = glm::max(0, posX - 3); x <= glm::min(maskTexture.width() - 1, posX + 3); x++)
			maskTexture.setPixel(x, y, NON_BLOCKING_PIXEL);
}

void Scene::selectLemming(int mouseX, int mouseY, int skill)
{
	vec2 selectPos = calculateMouseToMapCoord(mouseX, mouseY);
	bool exit = false;
	for (int i = 0; !exit && i < numLemmingsActivated; i++) {
		if (lemmings[i]->isActive() && isSelected(selectPos, lemmings[i]->position())) {
			lemmings[i]->setSelected(true);
			lemmings[i]->setSkill(skill);
			exit = true;
		}
	}
}

bool Scene::isSelected(glm::vec2 selectPos, glm::vec2 pos)
{
	float distance = distanceVec2(selectPos, pos);
	if (distance <= 10.f) return true;
	else return false;
}

float Scene::distanceVec2(glm::vec2 p1, glm::vec2 p2)
{
	float diffY = p1.y - p2.y;
	float diffX = p1.x - p2.x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}

void Scene::applyMask(int mouseX, int mouseY)
{
	glm::vec2 pos = calculateMouseToMapCoord(mouseX, mouseY);
	for (int y = glm::max(0, (int)pos.y - 3); y <= glm::min(maskTexture.height() - 1, (int)pos.y + 3); y++)
		for (int x = glm::max(0, (int)pos.x - 3); x <= glm::min(maskTexture.width() - 1, (int)pos.x + 3); x++)
			maskTexture.setPixel(x, y, MAP_BLOCKING_PIXEL);
}

void Scene::applyMaskLEM(int posX, int posY)
{
	for (int y = glm::max(0, (int)posY - 7); y <= glm::min(maskTexture.height() - 1, (int)posY + 7); y++)
		for (int x = glm::max(0, (int)posX - 7); x <= glm::min(maskTexture.width() - 1, (int)posX + 7); x++)
			maskTexture.setPixel(x, y, LEM_BLOCKING_PIXEL);
}

int Scene::getNumLemmingsReachedExitDoor()
{
	return numLemmingsReachedExitDoor;
}

int Scene::getNumLemmingsToWin()
{
	return numLemmingsToWin;
}

int Scene::getNumLemmingsAlive()
{
	return numTotalLemmings - numLemmingsDead;
}

int Scene::getMinutesLeft()
{
	return maxTime/1000 / 60;
}

int Scene::getSecondsLeft()
{
	return maxTime/1000 % 60;
}

void Scene::eraseMaskCircle(glm::ivec2 position)
{
	int posX, posY;
	int radius = 15;
	int limite = ceil(sqrt(radius*radius * 2));
	posX = position.x;
	posY = position.y;
	for (int y = glm::max(0, posY - limite); y <= glm::min(maskTexture.height() - 1, posY + limite); y++) {
		for (int x = glm::max(0, posX - limite); x <= glm::min(maskTexture.width() - 1, posX + limite); x++) {
			int dx = x - posX;
			int dy = y - posY;
			int distance = dx * dx + dy * dy;
			if (distance < radius*radius)
				maskTexture.setPixel(x, y, NON_BLOCKING_PIXEL);

		}

	}
	eraseMask(position);
}

glm::vec2 Scene::getPosCamera()
{
	return levelCameraInitialPos[currentLevel];
}

void Scene::eraseMask(glm::ivec2 position)
{
	eraseMaskDigging(position.x, position.y);
}

void Scene::testDig()
{
	isTestDig = !isTestDig;
}

void Scene::testParachute()
{
	isTestParachute = !isTestParachute;
}

void Scene::selectionMode(int skill) {

	if (!isSelectionMode) { //caso en el que ya se habia selecionado otra habilidad
		isSelectionMode = true;
	}
	else if (skill == this->skill && isSelectionMode)	//caso en el que se quiere desactivar una habilidad
	{
		this->skill = -1;
		isSelectionMode = false;
	}
	this->skill = skill;
}

void Scene::setClickableMode(bool b)
{
	this->isClickableMode = b;
}

vec2 Scene::getExitDoorPos()
{
	return levelLemmingsExitPos[currentLevel];
}

void Scene::lemmingDeath(int lemmingID)
{
	numLemmingActives--;
	numLemmingsDead += 1;
	lemmings[lemmingID]->setActive(false);
}

void Scene::lemmingReachedExit(int lemmingID)
{
	cout << "Lemming: " << lemmingID << " has reached the exit door" << endl;
	numLemmingsReachedExitDoor++;
	lemmings[lemmingID]->setActive(false);
}

void Scene::setGateOpened(bool opened)
{
	isGateOpened = opened;
}

void Scene::deleteLemming(int i)
{
	lemmingDeath(i);
	numLemmingsDead += 1;
	lemmings[i]->setActive(false);
}

void Scene::deleteAll()
{
	for (int i = 0; i < numTotalLemmings; i++) {
		deleteLemming(i);
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleTexProgram.init();
	simpleTexProgram.addShader(vShader);
	simpleTexProgram.addShader(fShader);
	simpleTexProgram.link();
	if (!simpleTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleTexProgram.log() << endl << endl;
	}
	simpleTexProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();

	vShader.initFromFile(VERTEX_SHADER, "shaders/maskedTexture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/maskedTexture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	maskedTexProgram.init();
	maskedTexProgram.addShader(vShader);
	maskedTexProgram.addShader(fShader);
	maskedTexProgram.link();
	if (!maskedTexProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << maskedTexProgram.log() << endl << endl;
	}
	maskedTexProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();

}

