#pragma once
#include "Framework/Base/Component/Scene/SceneComponent.h"

class CRenderComponent abstract :
    public CSceneComponent
{
public :
    bool bUseRender;

    bool bUseCameraPosition;

private :
    int32 SortingOrder;

public :
    CRenderComponent();

public :
    virtual void Render(HDC hdc) { }

public :
    void SetSortingOrder(int32 order);

    FORCEINLINE int32 GetSortingOrder() const
    { return SortingOrder; }

    class CScene* GetActiveScene() const;

    FVector ToCameraPosition(const FVector& scenePosition) const;

    virtual FVector ToRenderPosition(const FVector& scenePosition) const;

};

