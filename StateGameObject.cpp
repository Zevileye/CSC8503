#include "StateGameObject.h" 
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/State.h"
#include "../CSC8503Common/Debug.cpp"
#include "PartB.h"
using namespace NCL ;
using namespace CSC8503;

StateGameObject::StateGameObject() 
	: grid(nullptr)
	, weakState(false)
{
	home = Vector3(80, 0, 10);
	target = Vector3(80, 0, 80);

	counter = 0.0f;
	stateMachine = new StateMachine();

	State* stateA = new State([&](float dt) -> void
		{
			this->MoveToTarget(dt);
		}
	);
	State* stateB = new State([&](float dt) -> void
		{
			this->MoveToHome(dt);
		}
	);

	stateMachine->AddState(stateA);
	stateMachine->AddState(stateB);

	stateMachine->AddTransition(new StateTransition(stateA, stateB,
		[&]() -> bool
		{
			return this->weakState;
		}
	));

	stateMachine->AddTransition(new StateTransition(stateB, stateA,
		[&]() -> bool
		{
			return !this->weakState;
		}
	));
}

StateGameObject ::~StateGameObject() {
	delete stateMachine;
}

void StateGameObject::Update(float dt) {
	stateMachine->Update(dt);
}

Vector3 NCL::CSC8503::StateGameObject::OffsetPoint(const Vector3& v)
{
	auto size = grid->getNodeSize() * 0.5;
	return Vector3(v.x + size, v.y, v.z + size);
}

void StateGameObject::MoveLeft(float dt) {
	GetPhysicsObject()->AddForce({ -100 , 0 , 0 });
	counter += dt;
}

void StateGameObject::MoveRight(float dt) {
	GetPhysicsObject()->AddForce({ 100 , 0 , 0 });
		
	counter -= dt;
}

void StateGameObject::MoveToTarget(float dt)
{
	this->GetRenderObject()->SetColour(Vector4(1, 1, 1, 1));
	if (AutoMove(target))
	{
		weakState = true;
	}
}

void NCL::CSC8503::StateGameObject::MoveToHome(float dt)
{
	this->GetRenderObject()->SetColour(Vector4(1, 0, 0, 1));
	if (AutoMove(home))
	{
		weakState = false;
	}

	partB->setFinish(false);
}

void StateGameObject::DebugRunLine(NavigationPath outPath)
{
	vector < Vector3 > testNodes;
	Vector3 pos;
	while (outPath.PopWaypoint(pos)) {
		testNodes.push_back(pos);
		for (int i = 1; i < testNodes.size(); ++i) {
			Vector3 a = testNodes[i - 1];
			Vector3 b = testNodes[i];

			Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
		}
	}
}

bool NCL::CSC8503::StateGameObject::AutoMove(Vector3 end)
{
	bool isfinish = true;;
	if (grid)
	{
		NavigationPath outPath;
		Vector3 currentPos = GetTransform().GetPosition();
		grid->FindPath(OffsetPoint(currentPos), OffsetPoint(end), outPath);
		DebugRunLine(outPath);
		Vector3 pos;
		if (outPath.PopWaypoint(pos))
		{
			if (outPath.PopWaypoint(pos))
			{
				Vector3 vec = pos - currentPos;
				vec.y = 0;
				vec.Normalise();
				vec *= 10;
				GetPhysicsObject()->AddForce({ vec.x , 0 , vec.z });

				isfinish = false;
			}
		}
	}

	return isfinish;

}
