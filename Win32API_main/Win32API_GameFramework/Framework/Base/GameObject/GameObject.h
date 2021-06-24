#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

#include "Framework/Single/CollisionManager/CollisionManager.h"

#include "Framework/Base/Component/Scene/Render/RenderComponent.h"

#include "Framework/Base/Component/Scene/Collision/CollisionComponent.h"

class CGameObject :
    public CObject
{
private :
	list<CComponent*> CreatedComponents;

	list<CComponent*> UsedComponents;

	list<CComponent*> DestroyedComponents;

public :
	class CScene* OwnerScene;

	tstring Name;

	FVector Position;

	bool bCanEverTick;
	
	bool bIsStarted;

	bool bBeDestroy;

public :
	CGameObject();

public :
	virtual void Initialize() override;

	virtual void Start();

	virtual void Tick(float DeltaSeconds);

	virtual void OnDestroy();

	virtual void Release() override;

private :
	void RegisterNewRenderComponent(CRenderComponent* newRenderComponent);

public :
	template<typename T>
	FORCEINLINE static T* NewObject(class CScene * ownerScene, tstring objName)
	{
		T* newObject = new T();
		newObject->OwnerScene = ownerScene;
		newObject->Name = objName;

		newObject->Initialize();

		return newObject;
	}

	template<typename ComponentClassType>
	ComponentClassType* AddComponent()
	{
		if (!IsA<CComponent, ComponentClassType>())
		{
			LOG(ToTString(typeid(ComponentClassType).name()) << TEXT("은 CComponent 와 상속 관계가 아닙니다."));
			return nullptr;
		}

		CComponent* newComponent = CComponent::NewComponent<ComponentClassType>(this);
		CreatedComponents.push_back(newComponent);

		if (IsA<CRenderComponent, ComponentClassType>())
			RegisterNewRenderComponent(Cast<CRenderComponent>(newComponent));

		else if (IsA<CCollisionComponent, ComponentClassType>())
			CCollisionManager::Instance()->RegisterCollision(Cast<CCollisionComponent>(newComponent));

		return Cast<ComponentClassType>(newComponent);
	}

	template<typename ComponentClassType>
	ComponentClassType* GetComponent() const
	{
		for (auto iter = CreatedComponents.begin(); iter != CreatedComponents.end(); ++iter)
		{
			if (IsA<ComponentClassType>((*iter)))
				return Cast<ComponentClassType>(*iter);
		}

		for (auto iter = UsedComponents.begin(); iter != UsedComponents.end(); ++iter)
		{
			if (IsA<ComponentClassType>((*iter)))
			{
				if (!(*iter)->bBeDestroy)
					return Cast<ComponentClassType>(*iter);
			}
		}
		return nullptr;
	}

	void RemoveComponent(CComponent* component);

	
};

