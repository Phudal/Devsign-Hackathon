#include "GameObject.h"

#include "Framework/Base/Scene/Scene.h"

CGameObject::CGameObject()
{
	OwnerScene = nullptr;

	bCanEverTick = true;
	bIsStarted = bBeDestroy = false;
}

void CGameObject::Initialize()
{
	super::Initialize();
}

void CGameObject::Start()
{
	bIsStarted = true;
}

void CGameObject::Tick(float DeltaSeconds)
{
	if (CreatedComponents.size() > 0)
	{
		for (auto createdComponent : CreatedComponents)
			UsedComponents.push_back(createdComponent);
		CreatedComponents.clear();
	}
	
	if (DestroyedComponents.size() > 0)
	{
		for (auto destroyedComponent : DestroyedComponents)
		{
			UsedComponents.remove(destroyedComponent);

			if (IsA<CRenderComponent>(destroyedComponent))
				OwnerScene->UnRegisterRenderComponent(
					Cast<CRenderComponent>(destroyedComponent));

			else if (IsA<CCollisionComponent>(destroyedComponent))
				CCollisionManager::Instance()->UnRegisterCollision(
					Cast<CCollisionComponent>(destroyedComponent));

			CObject::DeleteObject(destroyedComponent);
		}
		DestroyedComponents.clear();
	}

	if (UsedComponents.size() > 0)
	{
		for (auto component : UsedComponents)
		{
			if (component->bBeDestroy) continue;

			if (!component->bIsStarted)
				component->Start();

			if (component->bCanEverTick)
				component->Tick(DeltaSeconds);
		}
	}
}

void CGameObject::OnDestroy()
{
	if (CreatedComponents.size() > 0)
	{
		for (auto createdComponent : CreatedComponents)
			RemoveComponent(createdComponent);
	}

	if (UsedComponents.size() > 0)
	{
		for (auto component : UsedComponents)
			RemoveComponent(component);
	}
}

void CGameObject::Release()
{
	super::Release();

	CreatedComponents.clear();
	UsedComponents.clear();

	if (DestroyedComponents.size() > 0)
	{
		for (auto destroyedComponent : DestroyedComponents)
		{
			if (IsA<CRenderComponent>(destroyedComponent))
				OwnerScene->UnRegisterRenderComponent(Cast<CRenderComponent>(destroyedComponent));

			else if (IsA<CCollisionComponent>(destroyedComponent))
				CCollisionManager::Instance()->UnRegisterCollision(
					Cast<CCollisionComponent>(destroyedComponent));

			CObject::DeleteObject(destroyedComponent);
		}

		DestroyedComponents.clear();
	}

}

void CGameObject::RegisterNewRenderComponent(
	CRenderComponent* newRenderComponent)
{ OwnerScene->RegisterNewRenderComponent(newRenderComponent); }

void CGameObject::RemoveComponent(CComponent* component)
{
	if (component->bBeDestroy) return;

	component->bBeDestroy = true;
	DestroyedComponents.push_back(component);
}
