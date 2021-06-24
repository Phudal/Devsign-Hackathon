#pragma once

#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

class CComponent abstract :
    public CObject
{

public :
    class CGameObject* Owner;

    bool bCanEverTick;

    bool bIsStarted;

    bool bBeDestroy;

public :
    CComponent();

public :
    virtual void Start();
    FORCEINLINE virtual void Tick(float deltaSeconds) {};

public :
    template<typename T>
    FORCEINLINE static T* NewComponent(class CGameObject * ownerGameObject)
    {
        if (!IsA<CComponent, T>()) return nullptr;

        T* newComponent = new T();
        newComponent->Owner = ownerGameObject;
        newComponent->Initialize();

        return newComponent;
    }
};

