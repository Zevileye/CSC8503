#pragma once
#include "..\CSC8503Common\GameObject.h"
#include "../CSC8503Common/NavigationGrid.h"
namespace NCL {
	namespace CSC8503 {
		class PartA;
		class PartAGameObject : public GameObject
		{
		public:
			virtual void OnCollisionBegin(GameObject* otherObject);
			void SetPartA(PartA* partA) { this->partA = partA; }
		protected:

			PartA* partA;
		};
	}
}
