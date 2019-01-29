#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "Menu.h"
#include "Instructions.h"
#include "Credits.h"
#include "Win.h"
#include "lose.h"
#include "levelSelection.h"


// Game is a singleton (a class with a single instance) that represents our whole application

class Game;

class State
{

public:
	~State();
	virtual void init(Game* pContext) = 0;
	virtual void update(Game* pContext, int deltaTime) = 0;
	virtual void render(Game* pContext) = 0;
	virtual bool isActiveButtons() = 0;
protected:
	State();

};

class MenuState : public State
{
public:
	MenuState();
	~MenuState();
	virtual void init(Game *pContext);
	virtual void update(Game* pContext, int deltaTime);
	virtual void render(Game* pContext);
	virtual bool isActiveButtons();
protected:
private:
};

class PlayingState : public State
{
public:
	PlayingState();
	~PlayingState();
	virtual void init(Game *pContext);
	virtual void update(Game* pContext, int deltaTime);
	virtual void render(Game* pContext);
	virtual bool isActiveButtons();
protected:
private:
};

class InstructionsState : public State
{
public:
	InstructionsState();
	~InstructionsState();
	virtual void init(Game *pContext);
	virtual void update(Game* pContext, int deltaTime);
	virtual void render(Game* pContext);
	virtual bool isActiveButtons();
protected:
private:
};

class CreditsState : public State
{
public:
	CreditsState();
	~CreditsState();
	virtual void init(Game *pContext);
	virtual void update(Game* pContext, int deltaTime);
	virtual void render(Game* pContext);
	virtual bool isActiveButtons();
protected:
private:
};

class levelSelectionState : public State
{
public:
	levelSelectionState();
	~levelSelectionState();
	virtual void init(Game *pContext);
	virtual void update(Game* pContext, int deltaTime);
	virtual void render(Game* pContext);
	virtual bool isActiveButtons();
protected:
private:
};

class WinState : public State
{
public:
	WinState();
	~WinState();
	virtual void init(Game *pContext);
	virtual void update(Game* pContext, int deltaTime);
	virtual void render(Game* pContext);
	virtual bool isActiveButtons();

protected:
private:
};

class LoseState : public State
{
public:
	LoseState();
	~LoseState();
	virtual void init(Game *pContext);
	virtual void update(Game* pContext, int deltaTime);
	virtual void render(Game* pContext);
	virtual bool isActiveButtons();
protected:
private:
};

class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void deleteAll();
	void changeGameVelocity();
	void pauseGame();
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	//STATES

	///menu
	void loadMenu();
	void updateMenu(int deltaTime);
	void renderMenu();
	void changeToMenuState();
	void menuClicked(int mouseX, int mouseY);

	//Scene
	void loadScene();
	void updateScene(int deltaTime);
	void renderScene();
	void changeToPlayState();

	//Instructions
	void loadInstructions();
	void updateInstructions(int deltaTime);
	void renderInstructions();
	void changeToInstructionsState();

	//Credits
	void loadCredits();
	void updateCredits(int deltaTime);
	void renderCredits();
	void changeToCreditsState();

	//levelSelection
	void loadLevelSelection();
	void updateLevelSelection(int deltaTime);
	void renderLevelSelection();
	void changeToLevelSelectionState();
	int getLevel();

	//Win
	void loadWin();
	void updateWin(int deltaTime);
	void renderWin();
	void changeToWinState();

	//Lose
	void loadLose();
	void updateLose(int deltaTime);
	void renderLose();
	void changeToLoseState();
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	bool between(int x, int y, glm::vec2 p1, glm::vec2 p2);
	bool getLeftMouse();

	int getNumLemmingsReachedExitDoor();
	int getNumLemmingsToWin();
	int getNumLemmingsAlive();
	int getMinutesLeft();
	int getSecondsLeft();
	glm::vec2 getMousePos();
	void selectSkill(int skill);

private:
	
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int mouseX, mouseY;               // Mouse position
	bool bLeftMouse, bRightMouse;     // Mouse button states
	State* state;
	string estado;
	Menu menu;
	Instructions instructions;
	Credits credits;
	levelSelection levelSelection;
	Win win;
	Lose lose;
	ShaderProgram texProgram;

};


#endif // _GAME_INCLUDE


