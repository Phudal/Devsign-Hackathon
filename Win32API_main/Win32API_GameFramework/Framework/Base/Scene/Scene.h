#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Base/GameObject/GameObject.h"

#include "Framework/Struct/DebugDrawInfo/DebugDrawInfo.h"

class CScene abstract :
    public CObject
{

private :
    list<CGameObject*> UsedGameObjectList;

    list<CGameObject*> CreatedGameObjectList;

    list<CGameObject*> DestroyedGameObjectList;

    list<class CRenderComponent*> CreatedRenderComponents;

    list<class CRenderComponent*> UsedRenderComponents;

    list<class CRenderComponent*> DestroyedRenderComponents;

    list<struct FDebugDrawInfo*> DebugDrawInfos;

    class CBitmap* BackBuffer, *Eraser;

    FThread* SortingOrderThread;
    bool bDoSortRenderComponent;

    class CScreenObject* Screen;

public :
    bool bNeedSort;

    FVector CameraPosition;

private:
    void SortRenderComponent();

public :
    virtual void Initialize() override;

    virtual void Tick(float deltaSecond);

    virtual void Render(HDC hdc);

    virtual void Release() override;

public :
    template<typename T>
    FORCEINLINE T* NewGameObject(
        tstring objName = tstring(TEXT("New GameObject")))
    {
        if (!IsA<CGameObject, T>())
        {
            LOGF(ToTString(typeid(T).name()) << TEXT(" 형식은 CGameObject 형식이 아닙니다."));
            return nullptr;
        }

        T* newGameObject = CGameObject::NewObject<T>(this, objName);
        CreatedGameObjectList.push_back(newGameObject);

        return newGameObject;
    }

    void Destroy(CGameObject* gameObject);

    FORCEINLINE void RegisterNewRenderComponent(
        class CRenderComponent * newRenderComponent)
    { CreatedRenderComponents.push_back(newRenderComponent); }

    FORCEINLINE void UnRegisterRenderComponent(
        class CRenderComponent* renderComponent)
    { DestroyedRenderComponents.push_back(renderComponent); }

    FORCEINLINE void DrawCircle(FVector center, FVector size,
        COLORREF color, float duration = 5.0f, bool bFill = false)
    { AddDebugDraw(EDebugDrawType::DT_Circle, center, size, color, duration, bFill); }

    FORCEINLINE void DrawRect(FVector center, FVector size,
        COLORREF color, float duration = 5.0f, bool bFill = false)
    { AddDebugDraw(EDebugDrawType::DT_Rect, center, size, color, duration, bFill); }

    FORCEINLINE void DrawLine(FVector start, FVector end,
        COLORREF color, float duration = 5.0f, bool bFill = false)
    { AddDebugDraw(EDebugDrawType::DT_LINE, start, end, color, duration, bFill); }

    FORCEINLINE void MoveCamera(FVector velocity)
    { CameraPosition += (velocity * -1.0f); }

    FORCEINLINE class CScreenObject* GetScreen() const
    { return Screen; }

    FORCEINLINE class CBitmap* GetBackBuffer() const
    { return BackBuffer; }


private :
    void AddDebugDraw(EDebugDrawType debugDrawType, FVector vec1, FVector vec2,
        COLORREF color, float duration, bool bFill);

};

