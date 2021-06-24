#pragma once
#pragma warning (disable : 26812)

#include "Framework/Base/Component/Scene/SceneComponent.h"

#include "Framework/Struct/Rect/Rect.h"

#include "Framework/Enum/CollisionType.h"

class CCollisionComponent abstract :
    public CSceneComponent
{
protected :
    FRect Bounds;

    ECollisionType::Type CollisionType;

public :
    vector< function<void(CCollisionComponent*)> > OverlapEvents;

public :
    virtual void OnOverlapped(CCollisionComponent* other);

    virtual void Tick(float dt) override;

protected :
    virtual void UpdateBounds() PURE;

public :
    FORCEINLINE const FRect& GetBounds() const
    { return Bounds; }

    FORCEINLINE ECollisionType::Type GetCollisionType() const
    { return CollisionType; }

};

