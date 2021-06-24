#include "Component.h"

#include "Framework/Base/GameObject/GameObject.h"

CComponent::CComponent()
{
	Owner = nullptr;
	bCanEverTick = true;
	bIsStarted = false;
	bBeDestroy = false;
}

void CComponent::Start()
{
	bIsStarted = true;
}
