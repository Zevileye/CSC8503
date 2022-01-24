#include "StatePlayerGameObject.h"
#include "PartB.h"

void NCL::CSC8503::StatePlayerGameObject::OnCollisionBegin(GameObject* otherObject) {
	if (otherObject->GetLayer() == layerCacheable)
	{
		if (partB->isFinished() == false)
		{
			world->RemoveGameObject(otherObject);
			score += 1;

			if (this->count == score)
			{
				partB->setFinish(true);
			}
		}
	}
}

void NCL::CSC8503::StatePlayerGameObject::SetPartB(PartB* partB) { this->partB = partB; }
