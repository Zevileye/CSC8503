#include "PartB.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Common/TextureLoader.h"

void NCL::CSC8503::PartB::UpdateGame(float dt)
{
	player->PrintScore(renderer);

	UpdateViewMode(dt);

	physics->Update(dt);

	world->UpdateWorld(dt);
	renderer->Update(dt);

	Debug::FlushRenderables(dt);
	renderer->Render();

	if (enemy)
	{
		enemy->Update(dt);
	}

	enemy->SetTarget(player->GetTransform().GetPosition());

	ControlPlayer();
	UpdateTime(dt);
	UpdateRestart();
}

void PartB::ControlPlayer()
{
	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LEFT)) {
		player->GetPhysicsObject()->AddForce(Vector3(0, 0, -5));
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
		player->GetPhysicsObject()->AddForce(Vector3(0, 0, 5));
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::UP)) {
		player->GetPhysicsObject()->AddForce(Vector3(5, 0, 0));
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::DOWN)) {
		player->GetPhysicsObject()->AddForce(Vector3(-5, 0, 0));
	}
}

void NCL::CSC8503::PartB::InitialiseScene()
{
	time = 60;
	finished = false;
	failed = true;

	tex1 = (OGLTexture*)TextureLoader::LoadAPITexture("doge.png");
	tex2 = (OGLTexture*)TextureLoader::LoadAPITexture("nyan.png");

	physics->UseGravity(true);

	InitDefaultFloor();

	enemy = AddEnemyStateToWorld(Vector3(80, 0, 10));
	player = AddPlayerStateToWorld(Vector3(75, 10, 80));
	enemy->SetPartB(this);
	player->SetPartB(this);
	player->SetWorld(this->world);
	player->GetRenderObject()->SetDefaultTexture(tex1);
	TestPathfinding();
	CreateMaze();
	enemy->SetGrid(grid);
}

void NCL::CSC8503::PartB::UpdateTime(float dt)
{
	if (finished == false)
	{
		time -= dt;
	}
	int inttime = (int)time;
	char temp[256];

	if (inttime < 0)
	{
		this->setFinish(false);
		inttime = 0;
	}
	_itoa_s(inttime, temp, 10);
	std::string str = "Time:";
	renderer->DrawString(str + temp, Vector2(5, 20));
}

void NCL::CSC8503::PartB::UpdateRestart()
{
	if (finished)
	{
		if (failed)
		{
			renderer->DrawString("Failed. (R)estart game", Vector2(30, 40));
		}
		else
		{
			renderer->DrawString("Successed. (R)estart game", Vector2(30, 40));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::R)) {
			this->InitialiseAssets();
		}
	}
}
