#include "GameSwitch.h"

#include "../CSC8503Common/Debug.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/State.h"

using namespace NCL;
using namespace CSC8503;

GameSwitch::GameSwitch()
	: isInMenu(false)
{
	partA = new PartA();
	partB = new PartB();
	mainMenu = new MainMenu();
	game = mainMenu;

	stateMachine = new StateMachine();

	State* stateMainMenu = new State([&](float dt) -> void
		{
			UpdateMainMenu(dt);
		}
	);

	State* statePartA = new State([&](float dt) -> void
		{
			UpdatePartGame(dt);
		}
	);
	State* statePartB = new State([&](float dt) -> void
		{
			UpdatePartGame(dt);
		}
	);

	stateMachine->AddState(stateMainMenu);
	stateMachine->AddState(statePartA);
	stateMachine->AddState(statePartB);

	stateMachine->AddTransition(new StateTransition(stateMainMenu, statePartA,
		[&]() -> bool
		{
			return this->game == partA;
		}
	));

	stateMachine->AddTransition(new StateTransition(stateMainMenu, statePartB,
		[&]() -> bool
		{
			return this->game == partB;
		}
	));

	stateMachine->AddTransition(new StateTransition(statePartA, stateMainMenu,
		[&]() -> bool
		{
			return this->game == mainMenu;
		}
	));

	stateMachine->AddTransition(new StateTransition(statePartB, stateMainMenu,
		[&]() -> bool
		{
			return this->game == mainMenu;
		}
	));
}

void GameSwitch::Update(float dt)
{
	stateMachine->Update(dt);
	game->UpdateGame(dt);
}

void GameSwitch::UpdateMainMenu(float dt)
{
	NCL::Debug::Print("Welcome to the Demo", Vector2(30, 35));
	NCL::Debug::Print("Enter Part(A) game", Vector2(30, 45));
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::A)) {
		game = partA;
		game->InitialiseAssets();
		isInMenu = false;
	}
	NCL::Debug::Print("Enter Part(B) game", Vector2(30, 55));
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::B)) {
		game = partB;
		game->InitialiseAssets();
		isInMenu = false;
	}
	NCL::Debug::Print("(esc) to quit", Vector2(30, 65));
}

void GameSwitch::UpdatePartGame(float dt)
{
	if (isInMenu)
	{
		NCL::Debug::Print("(T)urn to main menu", Vector2(5, 85));
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::T)) {
			game = mainMenu;
			game->InitialiseAssets();
			isInMenu = false;
		}

		NCL::Debug::Print("(E)ixt menu", Vector2(5, 95));
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::E)) {
			isInMenu = false;
		}
	}
	else
	{
		NCL::Debug::Print("(M)enu", Vector2(5, 95));
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::M)) {
			isInMenu = true;
		}
	}
}
