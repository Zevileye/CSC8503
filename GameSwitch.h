#pragma once

#include "PartA.h"
#include "PartB.h"
#include "MainMenu.h"

class GameSwitch
{
public:
	GameSwitch();

	void Initialise()
	{
		game->InitialiseAssets();
	}

	void Update(float dt);

protected:
	void UpdateMainMenu(float dt);
	void UpdatePartGame(float dt);

private:
	TutorialGame* game;
	PartA* partA;
	PartB* partB;
	MainMenu* mainMenu;

	StateMachine* stateMachine;

	bool isInMenu;
};

