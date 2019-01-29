#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "MaskedTexturedQuad.h"
#include "Lemming.h"
#include "ButtonsBanner.h"
#include "Gate.h"
#include "common_defs.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void initGates();
	void updateThisScene(int deltaTime);
	void render();
	void mouseMoved(int mouseX, int mouseY, bool bLeftButton, bool bRightButton);
	void pauseScene();
	void changeGameVelocity();
	glm::vec2 getPosCamera();
	glm::vec2 getExitDoorPos();

	void eraseMask(glm::ivec2 position);
	void eraseMaskCircle(glm::ivec2 position);
	void testDig();
	void testParachute();
	void selectionMode(int skill);
	void setClickableMode(bool b);
	void deleteLemming(int i);
	void deleteAll();
	void loadLevel(int level);
	void initBanner();
	void lemmingDeath(int lemmingID);
	void lemmingReachedExit(int lemmingID);
	void setGateOpened(bool opened);
	void eraseMask(int mouseX, int mouseY);
	void eraseMaskPixel(int posX, int posY);
	void applyMask(int mouseX, int mouseY);
	void applyMaskLEM(int posX, int posY);
	int getNumLemmingsReachedExitDoor();
	int getNumLemmingsToWin();
	int getNumLemmingsAlive();
	int getMinutesLeft();
	int getSecondsLeft();

private:
	void initShaders();
	void initVariables();
	void initVariablesLevel();
	void initLemmings();
	void initCameraAndTexture();
	void loadMapQuadAndTexture();
	void updateThisSceneElements(int deltaTime);
	
	glm::vec2 calculateMouseToMapCoord(int mouseX, int mouseY);
	void manageScrolling(int mouseX, int mouseY);
	void checkCameraMove();
	void moveCamera(float left, float right, float bottom, float top);

	void updateCamera();

	void eraseMaskDigging(int mouseX, int mouseY);
	void selectLemming(int mouseX, int mouseY, int skill);
	bool isSelected(glm::vec2 selectPos, glm::vec2 pos);
	float distanceVec2(glm::vec2 selectPos, glm::vec2 pos);




private:
	Texture colorTexture;
	VariableTexture maskTexture;
	MaskedTexturedQuad *map;
	ShaderProgram simpleTexProgram, maskedTexProgram;
	float currentTime;
	glm::mat4 projection;
	vector<Lemming*> lemmings;
	Gate *entryGate, *exitGate;
	ButtonsBanner *banner;
	int numLemmingActives, numLemmingsActivated, numLemmingsReachedExitDoor, numTotalLemmings, numLemmingsToWin, numLemmingsDead;
	bool isDoubleVelocity, isPaused, isGateOpened;
	int currentLevel, velocityMultiplier, timeLastLemming, timeBetweenLemmings;

	glm::vec2 cameraDimensions;
	glm::vec2 levelCameraInitialPos[3];
	glm::vec2 levelLemmingsInitPos[3], levelLemmingsExitPos[3];
	std::string mapRoute[3], maskRoute[3];




	glm::vec2 mapSpriteDimensions[3], mapSpriteUtilPixels[3];
	float cameraLeft, cameraRight, cameraBottom, cameraTop;
	bool isScrollingLeft = false, isScrollingRight = false, isScrollingTop = false, isScrollingBottom = false, isTestDig = false, isTestParachute = false, isSelectionMode = false, isClickableMode = false;
	bool lemmingActivated;

	int skill = -1; //-1 no_selected, 0 dig, 1 parachute, 2 boom
	int maxTime;

};


#endif // _SCENE_INCLUDE
