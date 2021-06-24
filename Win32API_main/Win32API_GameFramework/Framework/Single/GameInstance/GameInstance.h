#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Interface/ManagerClass.h"

class CGameInstance :
    public CObject
{
protected :
    map <string, IManagerClass*> ManagerClasses;

private :
    HDC Hdc;

public :
    CGameInstance();

    virtual void Initialize() override;
    virtual void Release() override;

protected :
    template<typename ManagerClassType>
    FORCEINLINE void RegisterManagerClass()
    {
        if (!IsA<IManagerClass, ManagerClassType>()) return;

        IManagerClass* newSubManagerInstance = NewObject<ManagerClassType>();

        ManagerClasses.insert( make_pair(typeid(ManagerClassType).name(), newSubManagerInstance) );

        newSubManagerInstance->InitializeManagerClass();
    }

public :
    template<typename ManagerClassType>
    FORCEINLINE ManagerClassType* GetManagerClass()
    { return Cast<ManagerClassType>(ManagerClasses[string(typeid(ManagerClassType).name())]); }

    FORCEINLINE HDC & GetDC()
    { return Hdc; }
};

