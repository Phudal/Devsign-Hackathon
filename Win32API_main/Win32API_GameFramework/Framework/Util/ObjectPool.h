#pragma once
#include "Framework/Base/Object/Object.h"

#include "Framework/Interface/ObjectPoolable.h"

class CObjectPool final :
    public CObject
{
private :
    vector<IObjectPoolable*> PoolObjects;

public:
    template<typename T>
    FORCEINLINE T* RegisterRecyclableObject(T* newRecyclableObject)
    {
        PoolObjects.push_back(newRecyclableObject);
        return newRecyclableObject;
    }

    template<typename T>
    T* GetRecycledObject()
    { return GetRecycledObject<T>([](T* obj) { return true; }); }

    template<typename T>
    T* GetRecycledObject(function<bool(T* poolableObject)> pred)
    {
        if (PoolObjects.size() == 0) return nullptr;

        for (auto obj : PoolObjects)
        {
            if (obj->GetCanRecyclable())
            {
                if (!pred(Cast<T>(obj))) continue;

                obj->SetCanRecyclable(false);
                obj->OnRecycleStarted();
                return Cast<T>(obj);
            }
        }

        return nullptr;
    }

public :
    virtual void Release() override;
};

