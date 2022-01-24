#include "PartAGameObject.h"
#include "PartA.h"

void NCL::CSC8503::PartAGameObject::OnCollisionBegin(GameObject* otherObject)
{
	if (otherObject->GetLayer() == layerCacheable)
	{
		partA->setFinish();
	}
}
