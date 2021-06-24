#include "SceneComponent.h"
#include "Framework/Base/GameObject/GameObject.h"

CSceneComponent::CSceneComponent()
{
    RelativePosition = FVector::ZeroVector();
    RelativeScale = FVector::OneVector();
}

FVector CSceneComponent::GetComponentPosition() const
{
    return Owner->Position + RelativePosition;
}
