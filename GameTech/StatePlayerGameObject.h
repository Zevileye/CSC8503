#pragma once
#include "..\CSC8503Common\GameObject.h"
#include "../CSC8503Common/NavigationGrid.h"
#include "TutorialGame.h"

namespace NCL {
	namespace CSC8503 {
		class StateMachine;
		class PartB;
		class StatePlayerGameObject : public GameObject {
		public:
			StatePlayerGameObject()
				: world(nullptr)
				, score(0)
			{

			}

			void SetWorld(GameWorld* world)
			{
				this->world = world;
			}

			virtual void OnCollisionBegin(GameObject* otherObject);

			void PrintScore(GameTechRenderer* renderer)
			{
				char temp[256];
				_itoa_s(score, temp, 10);
				std::string str = "Score:";
				renderer->DrawString(str + temp, Vector2(5, 10));
			}

			void SetPartB(PartB* partB);
			void SetCount(int count)
			{
				this->count = count;
			}
		protected:
			GameWorld* world;
			int score;
			PartB* partB;
			int count;
		};		
	}
}

