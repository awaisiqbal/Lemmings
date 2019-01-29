#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "Game.h"
#include "SoundSystem.h"


#define KEY_ESCAPE 27
#define KEY_PAUSE 48 // 0
#define KEY_VELOCITY 49 // 1
#define KEY_DIGGER_ALL 50 // 2
#define KEY_PARACHUTE_ALL 51 // 3
#define KEY_DIGGER 52 //4
#define KEY_PARACHUTE 53 // 5
#define KEY_BOOM 54 //6
#define KEY_BLOCKER 55 //7
#define KEY_BASHER 56 //8
#define KEY_BOOM_ALL 57 // 9


//STATE

State::State() {}

State::~State() {}

//MENU

MenuState::MenuState() {}

MenuState::~MenuState() {}

void MenuState::init(Game* pContext)
{
	pContext->loadMenu();
}

void MenuState::update(Game* pContext, int deltaTime)
{
	pContext->updateMenu(deltaTime);
}

void MenuState::render(Game* pContext)
{
	pContext->renderMenu();
}

bool MenuState::isActiveButtons()
{
	return true;
}



//PLAYING STATE

PlayingState::PlayingState() {}

PlayingState::~PlayingState() {}

void PlayingState::init(Game* pContext)
{
	pContext->loadScene();
}

void PlayingState::update(Game* pContext, int deltaTime)
{
	pContext->updateScene(deltaTime);
}

void PlayingState::render(Game* pContext)
{
	pContext->renderScene();
}

bool PlayingState::isActiveButtons()
{
	return true;
}

//INSTRUCTIONS STATE

InstructionsState::InstructionsState() {}

InstructionsState::~InstructionsState() {}

void InstructionsState::init(Game* pContext)
{
	pContext->loadInstructions();

}

void InstructionsState::update(Game* pContext, int deltaTime)
{
	pContext->updateInstructions(deltaTime);
}

void InstructionsState::render(Game* pContext)
{

	pContext->renderInstructions();
}

bool InstructionsState::isActiveButtons()
{
	return true;
}

//CREDITS STATE

CreditsState::CreditsState() {}

CreditsState::~CreditsState() {}

void CreditsState::init(Game* pContext)
{
	pContext->loadCredits();
}

void CreditsState::update(Game* pContext, int deltaTime)
{
	pContext->updateCredits(deltaTime);
}

void CreditsState::render(Game* pContext)
{
	pContext->renderCredits();
}

bool CreditsState::isActiveButtons()
{
	return true;
}

//levelSelectionState

levelSelectionState::levelSelectionState() {}

levelSelectionState::~levelSelectionState() {}

void levelSelectionState::init(Game* pContext)
{
	pContext->loadLevelSelection();
}

void levelSelectionState::update(Game* pContext, int deltaTime)
{
	pContext->updateLevelSelection(deltaTime);
}

void levelSelectionState::render(Game* pContext)
{
	pContext->renderLevelSelection();
}

bool levelSelectionState::isActiveButtons()
{
	return true;
}


//winState

//WIN STATE

WinState::WinState() {}

WinState::~WinState() {}

void WinState::init(Game* pContext)
{
	pContext->loadWin();
}

void WinState::update(Game* pContext, int deltaTime)
{
	pContext->updateWin(deltaTime);
}

void WinState::render(Game* pContext)
{
	pContext->renderWin();
}

bool WinState::isActiveButtons()
{
	return false;
}

//LOSE STATE

LoseState::LoseState() {}

LoseState::~LoseState() {}

void LoseState::init(Game* pContext)
{
	pContext->loadLose();
}

void LoseState::update(Game* pContext, int deltaTime)
{
	pContext->updateLose(deltaTime);
}

void LoseState::render(Game* pContext)
{
	pContext->renderLose();
}

bool LoseState::isActiveButtons()
{
	return false;
}

//game
void Game::init()
{
	bPlay = true;
	bLeftMouse = bRightMouse = false;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	menu.init();
	scene.init();
	instructions.init();
	credits.init();
	levelSelection.init();
	win.init();
	lose.init();
	SoundSystem::instance().init();
	state = new MenuState();
	estado = "menu";
	state->init(this);
}

bool Game::update(int deltaTime)
{
	state->update(this, deltaTime);
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	state->render(this);
}

//STATES

//Menu

void Game::loadMenu() {
	menu.load();
}

void Game::updateMenu(int deltaTime)
{
	menu.update(deltaTime);
}

void Game::renderMenu()
{
	menu.render();
}

void Game::changeToMenuState()
{
	if (state != NULL)
	{
		delete state;
		state = NULL;
	}
	estado = "menu";
	this->state = new MenuState();
	state->init(this);
}

void Game::menuClicked(int mouseX, int mouseY)
{
	if (between(mouseX, mouseY, glm::vec2(157, 243), glm::vec2(280, 319))) changeToPlayState();
	else if (between(mouseX, mouseY, glm::vec2(599, 252), glm::vec2(875, 303))) changeToInstructionsState();
	else if (between(mouseX, mouseY, glm::vec2(273, 325), glm::vec2(444, 368))) changeToCreditsState();
	else if (between(mouseX, mouseY, glm::vec2(378, 251), glm::vec2(537, 293))) changeToLevelSelectionState();
	else if (between(mouseX, mouseY, glm::vec2(495, 333), glm::vec2(610, 371))) bPlay = false;
}
//Scene

void Game::loadScene()
{
	//scene.init();
	scene.loadLevel(getLevel());
}

void Game::updateScene(int deltaTime)
{
	scene.updateThisScene(deltaTime);
}

void Game::renderScene()
{
	scene.render();
}

void Game::changeToPlayState()
{
	SoundSystem::instance().restartSound();
	if (state != NULL)
	{
		delete state;
		state = NULL;
	}
	estado = "play";
	this->state = new PlayingState();
	state->init(this);
}

//instructions
void Game::loadInstructions() {
	instructions.load();
}

void Game::updateInstructions(int deltaTime)
{
	instructions.update(deltaTime);
}

void Game::renderInstructions()
{
	instructions.render();
}

void Game::changeToInstructionsState()
{
	if (state != NULL)
	{
		delete state;
		state = NULL;
	}
	estado = "instructions";
	this->state = new InstructionsState();
	this->state->init(this);
}

//credits
void Game::loadCredits() {
	credits.load();
}

void Game::updateCredits(int deltaTime)
{
	credits.update(deltaTime);
}

void Game::renderCredits()
{
	credits.render();
}

void Game::changeToCreditsState()
{
	if (state != NULL)
	{
		delete state;
		state = NULL;
	}
	this->state = new CreditsState();
	estado = "credits";
	this->state->init(this);
}
//levelSelection

void Game::loadLevelSelection() {
	levelSelection.load();
}

void Game::updateLevelSelection(int deltaTime)
{
	levelSelection.update(deltaTime);
}

void Game::renderLevelSelection()
{
	levelSelection.render();
}

void Game::changeToLevelSelectionState()
{
	if (state != NULL)
	{
		delete state;
		state = NULL;
	}
	this->state = new levelSelectionState();
	estado = "levelSelection";
	this->state->init(this);
}

int Game::getLevel()
{
	return levelSelection.getLevel();
}


//win


void Game::loadWin() {
	win.load();
}

void Game::updateWin(int deltaTime)
{
	win.update(deltaTime);
}

void Game::renderWin()
{
	win.render();
}

void Game::changeToWinState()
{
	if (state != NULL)
	{
		delete state;
		state = NULL;
	}
	estado = "win";
	this->state = new WinState();
	state->init(this);
}

//Lose

void Game::loadLose() {
	lose.load();
}

void Game::updateLose(int deltaTime)
{
	lose.update(deltaTime);
}

void Game::renderLose()
{
	lose.render();
}

void Game::changeToLoseState()
{
	if (state != NULL)
	{
		delete state;
		state = NULL;
	}
	estado = "lose";
	this->state = new LoseState();
	state->init(this);
}



//fin states
void Game::keyPressed(int key)
{
	cout << key << endl;
	if (key == KEY_ESCAPE) { // Escape code
		bPlay = false;
	}
	else if (key == KEY_PAUSE) { //Pause or resume game pressing 0
		pauseGame();
	}
	else if (key == KEY_VELOCITY)
	{
		changeGameVelocity();
	}
	else if (key == KEY_DIGGER_ALL) { //test excavar boton 2
		scene.testDig();
	}
	else if (key == KEY_PARACHUTE_ALL) { //test PARACHUTE BOTON 3
		scene.testParachute();
	}
	else if (key == KEY_DIGGER) { //boton 4
		scene.selectionMode(0);
	}
	else if (key == KEY_PARACHUTE) { // BOTON 5
		scene.selectionMode(1);
	}
	else if (key == KEY_BOOM) // Boton 6
	{
		scene.selectionMode(99);
	}
	else if (key == KEY_BLOCKER)	//boton 7
	{
		scene.selectionMode(2);
	}
	else if (key == KEY_BASHER)	//boton 8
	{
		scene.selectionMode(3);
	}
	else if (key == 'c') {
		scene.selectionMode(4);
	}
	else if (key == KEY_BOOM_ALL) // boton 9
	{
		deleteAll();

	}

	//test cambiar pantallas
	else if (key == 'q') { //q
		SoundSystem::instance().restartSound();
		SoundSystem::instance().playBackground();
		changeToMenuState();
	}
	else if (key == 'w') { //w 
		changeToPlayState();
	}
	else if (key == 'e') //e 
	{
		changeToInstructionsState();
	}
	else if (key == 'r') //r 
	{
		changeToCreditsState();
	}

	else if (key == 't') //T
	{
		changeToLevelSelectionState();
	}
	else if (key == 'y') //Y
	{
		changeToWinState();
	}
	else if (key == 'u') //Y
	{
		changeToLoseState();
	}
	keys[key] = true;
}

void Game::deleteAll()
{
	scene.deleteAll();
}

void Game::changeGameVelocity()
{
	scene.changeGameVelocity();
}

void Game::pauseGame()
{
	scene.pauseScene();
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
	if (estado == "play") scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
}

void Game::mousePress(int button)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		cout << "X: " << mouseX << " Y: " << mouseY << endl;
		bLeftMouse = true;
		/*if (estado == "menu") {
			menuClicked(mouseX, mouseY);
		}*/
		if (estado == "play") scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		bRightMouse = true;
		scene.mouseMoved(mouseX, mouseY, bLeftMouse, bRightMouse);
	}
}

void Game::mouseRelease(int button)
{
	if (button == GLUT_LEFT_BUTTON)
		bLeftMouse = false;
	else if (button == GLUT_RIGHT_BUTTON)
		bRightMouse = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

bool Game::between(int x, int y, glm::vec2 p1, glm::vec2 p2)
{
	if ((x >= p1.x && x <= p2.x) && (y >= p1.y && y <= p2.y)) return true;
	else return false;
}

bool Game::getLeftMouse()
{
	return bLeftMouse;
}

int Game::getNumLemmingsReachedExitDoor()
{
	return scene.getNumLemmingsReachedExitDoor();
}

int Game::getNumLemmingsToWin()
{
	return scene.getNumLemmingsToWin();
}

int Game::getNumLemmingsAlive()
{
	return scene.getNumLemmingsAlive();
}

int Game::getMinutesLeft()
{
	return scene.getMinutesLeft();
}

int Game::getSecondsLeft()
{
	return scene.getSecondsLeft();
}

glm::vec2 Game::getMousePos()
{
	return glm::vec2(mouseX, mouseY);
}



void Game::selectSkill(int skill) {
	scene.selectionMode(skill);
}




