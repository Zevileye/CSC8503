#include "PartA.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Common/TextureLoader.h"

void NCL::CSC8503::PartA::UpdateRestart()
{
	if (finished)
	{
		renderer->DrawString("Congrats! (R)estart game", Vector2(30, 40));

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::R)) {
			this->InitialiseAssets();
		}
	}
}

void NCL::CSC8503::PartA::InitialiseScene()
{
	time = 0;
	finished = false;

	physics->UseGravity(true);

	tex1 = (OGLTexture*)TextureLoader::LoadAPITexture("doge.png");

	InitDefaultFloor()->SetLayer(layerCacheable);

	InitialiseAllLevel();
}

GameObject* NCL::CSC8503::PartA::AddOBBCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass)
{
	GameObject* cube = new GameObject();

	OBBVolume* volume = new OBBVolume(dimensions);

	cube->SetBoundingVolume((CollisionVolume*)volume);

	cube->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2);

	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, basicTex, basicShader));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(cube);

	return cube;
}

PartAGameObject* NCL::CSC8503::PartA::AddPartAGameObjectToWorld(const Vector3& position, float radius, float inverseMass)
{
	PartAGameObject* sphere = new PartAGameObject();

	Vector3 sphereSize = Vector3(radius, radius, radius);
	SphereVolume* volume = new SphereVolume(radius);
	sphere->SetBoundingVolume((CollisionVolume*)volume);

	sphere->GetTransform()
		.SetScale(sphereSize)
		.SetPosition(position);

	sphere->SetRenderObject(new RenderObject(&sphere->GetTransform(), sphereMesh, basicTex, basicShader));
	sphere->SetPhysicsObject(new PhysicsObject(&sphere->GetTransform(), sphere->GetBoundingVolume()));

	sphere->GetPhysicsObject()->SetInverseMass(inverseMass);
	sphere->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(sphere);

	return sphere;
}

void NCL::CSC8503::PartA::InitialiseAllLevel()
{
	InitialiseLevel1();
	InitialiseLevel2();
}

void NCL::CSC8503::PartA::InitialiseLevel1()
{
	float level1BaseHeight = 30.0f;
	{
		Vector3 position = Vector3(10.0f, level1BaseHeight + 10.0f, 0.0f);
		Vector3 cubeDims = Vector3(1, 10, 10);
		AddCubeToWorld(position, cubeDims, 0.0);
	}
	{
		Vector3 position = Vector3(0.0f, level1BaseHeight + 10.0f, -10.0f);
		Vector3 cubeDims = Vector3(10, 10, 1);
		AddCubeToWorld(position, cubeDims, 0.0);
	}
	{
		Vector3 position = Vector3(-10.0f, level1BaseHeight + 10.0f, 0.0f);
		Vector3 cubeDims = Vector3(1, 10, 10);
		AddCubeToWorld(position, cubeDims, 0.0);
	}

	// short plane
	{
		Vector3 position = Vector3(0.0f, level1BaseHeight + 15.0f, 10.0f);
		Vector3 cubeDims = Vector3(10, 3, 1);
		AddCubeToWorld(position, cubeDims, 0.0);
	}

	// bottom plane
	{
		Vector3 position = Vector3(0.0f, level1BaseHeight, 0.0f);
		Vector3 cubeDims = Vector3(10, 2, 10);
		AddCubeToWorld(position, cubeDims, 0.0);
	}

	// pusher1
	{
		Vector3 position = Vector3(5.0f, level1BaseHeight + 5.0f, -5.0f);
		Vector3 cubeDims = Vector3(8, 10, 2);
		pusher1 = AddCubeToWorld(position, cubeDims, 10.0);
	}

	// button1
	{
		Vector3 position = Vector3(10.0f, level1BaseHeight + 10.0f, 20.0f);
		Vector3 cubeDims = Vector3(1, 1, 1);
		button1 = AddCubeToWorld(position, cubeDims, 0.0);
	}

	{
		Vector3 position = Vector3(0.0f, level1BaseHeight + 5.0f, 0.0f);
		pellet = AddPartAGameObjectToWorld(position, 5.0, 1.0f);
		pellet->GetRenderObject()->SetDefaultTexture(tex1);
		pellet->SetPartA(this);
	}
}

void NCL::CSC8503::PartA::InitialiseLevel2()
{
	float level2BaseHeight = 10.0f;

	// slope
	{
		Vector3 position = Vector3(0.0f, level2BaseHeight + 10.0f, 30.0f);
		Vector3 cubeDims = Vector3(10, 1, 20);
		GameObject* ceil = AddOBBCubeToWorld(position, cubeDims, 0.0);
		ceil->GetRenderObject()->GetTransform()->SetOrientation(Quaternion::EulerAnglesToQuaternion(30, 0.0, 0.0));
	}
	{
		Vector3 position = Vector3(10.0f, level2BaseHeight + 10.0f, 60.0f);
		Vector3 cubeDims = Vector3(1, 15, 10);
		AddCubeToWorld(position, cubeDims, 0.0);
	}
	{
		Vector3 position = Vector3(0.0f, level2BaseHeight + 10.0f, 70.0f);
		Vector3 cubeDims = Vector3(10, 15, 1);
		AddCubeToWorld(position, cubeDims, 0.0);
	}

	// bottom plane
	{
		Vector3 position = Vector3(0.0f, level2BaseHeight - 3.0, 60.0f);
		Vector3 cubeDims = Vector3(10, 1, 10);
		AddCubeToWorld(position, cubeDims, 0.0);
	}

	// short plane
	{
		Vector3 position = Vector3(-10.0f, level2BaseHeight + 10.0f, 60.0f);
		Vector3 cubeDims = Vector3(1, 2, 10);
		AddCubeToWorld(position, cubeDims, 0.0);
	}

	// pusher2
	{
		Vector3 position = Vector3(0.0f, level2BaseHeight, 60.0f);
		Vector3 cubeDims = Vector3(10, 1, 9);
		pusher2 = AddCubeToWorld(position, cubeDims, 10.0);
	}
	// button2
	{
		Vector3 position = Vector3(-10.0f, level2BaseHeight + 10.0f, 80.0f);
		Vector3 cubeDims = Vector3(1, 1, 1);
		button2 = AddCubeToWorld(position, cubeDims, 0.0);
	}

	// ceil
	{
		Vector3 position = Vector3(0.0f, level2BaseHeight + 30.0f, 60.0f);
		Vector3 cubeDims = Vector3(30, 3, 10);
		GameObject* ceil = AddOBBCubeToWorld(position, cubeDims, 0.0);
		ceil->GetRenderObject()->GetTransform()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0.0, -30.0));
	}
}

void NCL::CSC8503::PartA::OnGameObjectClick(GameObject* obj)
{
	if (obj == button1)
	{
		pusher1->GetPhysicsObject()->AddForce(Vector3(0.0, 0.0, 150.0));
	}	
	else if (obj == button2)
	{
		pusher2->GetPhysicsObject()->AddForce(Vector3(0.0, 300.0, 0.0));
	}
}
