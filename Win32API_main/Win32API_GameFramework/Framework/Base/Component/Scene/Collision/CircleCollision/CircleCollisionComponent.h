#pragma once
#include "Framework/Base/Component/Scene/Collision/CollisionComponent.h"

class CCircleCollisionComponent :
    public CCollisionComponent
{
private :
    float Radius;

public :
    CCircleCollisionComponent();

protected :
    virtual void UpdateBounds() override;

public :
    void SetRadius(float radius);
    FORCEINLINE float GetRadius() const
    { return Radius; }

};

