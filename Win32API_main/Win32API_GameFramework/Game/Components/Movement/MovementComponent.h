#pragma once
#include "Framework/Base/Component/Component.h"

class CMovementComponent :
    public CComponent
{
private :
    FVector Impulse;

    FVector MovableAreaLT;
    FVector MovableAreaRB;

public:
    float MaxSpeed;

    float BrakingForce;

    FVector Velocity;

public :
    CMovementComponent();

public :
    virtual void Tick(float dt) override;

public :
    void AddImpulse(FVector impulse);

    void AddMovement(FVector direction);

    FORCEINLINE void SetMovableArea(const FVector& lt, const FVector& rb) 
    {
        MovableAreaLT = lt;
        MovableAreaRB = rb;
    }

    FORCEINLINE FVector& GetMovableAreaLT()
    { return MovableAreaLT; }

    FORCEINLINE FVector& GetMovableAreaRB()
    { return MovableAreaRB; }
};

