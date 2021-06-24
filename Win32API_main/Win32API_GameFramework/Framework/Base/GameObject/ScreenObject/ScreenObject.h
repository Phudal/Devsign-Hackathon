#pragma once
#include "Base/GameObject/GameObject.h"
#include "Base/Scene/Scene.h"
#include "Struct/Rect/Rect.h"

class CScreenObject :
    public CGameObject
{
private :
    FRect ScreenBounds;

    list<class CUIObject*> UIObjects;


public :
    CScreenObject();

private :
    void AddUIObject(class CUIObject* newUIObject);

public :
    template<typename T>
    FORCEINLINE T* CreateUIObject(tstring objectName = TEXT("New UI Object"))
    {
        T * newUIObject = OwnerScene->NewGameObject<T>(objectName);

        AddUIObject(newUIObject);

        return newUIObject;
    }

    void DestroyUIObject(class CUIObject* uiObject);

    FORCEINLINE const FRect& GetScreenBounds() const
    { return ScreenBounds; }

    FORCEINLINE void SetScreenBounds(FRect newScreenBounds)
    { ScreenBounds = newScreenBounds; }

};

