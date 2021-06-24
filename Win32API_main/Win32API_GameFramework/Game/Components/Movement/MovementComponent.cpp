#include "MovementComponent.h"
#include "Framework/Base/GameObject/GameObject.h"


CMovementComponent::CMovementComponent()
{
    Impulse = Velocity = FVector::ZeroVector();
    MaxSpeed = 600.0f;
    BrakingForce = 100.0f; // %

    MovableAreaLT = FVector::OneVector() * -999999.0f;
    MovableAreaRB = FVector::OneVector() * 999999.0f;
}

void CMovementComponent::Tick(float dt)
{
    super::Tick(dt);

    FVector& ownerPosition = Owner->Position;
    Owner->Position += (Velocity + Impulse) * dt;

    Velocity = FVector(
        FMath::Lerp(Velocity.X, 0.0f, dt * ((MaxSpeed * 0.01f) * BrakingForce * dt)),
        FMath::Lerp(Velocity.Y, 0.0f, dt * ((MaxSpeed * 0.01f) * BrakingForce * dt)));

    Impulse = FVector(
        FMath::Lerp(Impulse.X, 0.0f, dt * ((MaxSpeed * 0.01f) * BrakingForce * dt)),
        FMath::Lerp(Impulse.Y, 0.0f, dt * ((MaxSpeed * 0.01f) * BrakingForce * dt)));

    FRect movableArea(
        MovableAreaLT + (FVector::OneVector() * 1.0f),
        MovableAreaRB - (FVector::OneVector() * 1.0f));

    if (!FMath::IsIn(ownerPosition.X, MovableAreaLT.X, MovableAreaRB.X))
    {
        ownerPosition.X = FMath::Clamp(ownerPosition.X, MovableAreaLT.X + 2.0f, MovableAreaRB.X - 2.0f);
        Velocity.X = 0.0f;
    }

    if (!FMath::IsIn(ownerPosition.Y, MovableAreaLT.Y, MovableAreaRB.Y))
    {
        ownerPosition.Y = FMath::Clamp(ownerPosition.Y, MovableAreaLT.Y + 2.0f, MovableAreaRB.Y - 2.0f);
        Velocity.Y = 0.0f;
    }
}

void CMovementComponent::AddImpulse(FVector impulse)
{
    Impulse = impulse;
}

void CMovementComponent::AddMovement(FVector direction)
{
    Velocity += direction.Normalized() * MaxSpeed;

    if (Velocity.Length() > MaxSpeed)
    {
        Velocity.Normalize();
        Velocity *= MaxSpeed;
    }

}
