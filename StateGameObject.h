#pragma once
#include "..\CSC8503Common\GameObject.h"
#include "../CSC8503Common/NavigationGrid.h"
namespace NCL {
	namespace CSC8503 {
		class StateMachine;
		class PartB;
		class StateGameObject : public GameObject {
		public:
			StateGameObject();
			~StateGameObject();

			virtual void Update(float dt);

			void SetGrid(NavigationGrid* grid) { this->grid = grid; }
			void SetTarget(Vector3 target) { this->target = target; }
			void SetPartB(PartB* partB) { this->partB = partB; }

		protected:
			Vector3 OffsetPoint(const Vector3& v);

			void MoveLeft(float dt);
			void MoveRight(float dt);

			void MoveToTarget(float dt);
			void MoveToHome(float dt);
			void DebugRunLine(NavigationPath outPath);

			StateMachine* stateMachine;
			float counter;
			NavigationGrid* grid;
			Vector3 target;
			Vector3 home;

			bool weakState;
			PartB* partB;
		protected:
			bool AutoMove(Vector3 end);
		};
	}
}

