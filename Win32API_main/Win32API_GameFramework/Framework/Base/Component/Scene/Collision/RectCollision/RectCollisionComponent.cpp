#include "RectCollisionComponent.h"
#include "Framework/Base/GameObject/GameObject.h"

CRectCollisionComponent::CRectCollisionComponent() : 
	CRectCollisionComponent(FVector(0.0f, 0.0f)) { }

CRectCollisionComponent::CRectCollisionComponent(float size) : 
	CRectCollisionComponent(FVector(size, size)) { }

CRectCollisionComponent::CRectCollisionComponent(FVector size)
{
	Size = size;
	CollisionType = ECollisionType::Rect;
	Bounds = FRect(GetComponentPosition(), Size.X * RelativeScale.X, Size.Y * RelativeScale.Y);
}

void CRectCollisionComponent::UpdateBounds()
{
	Bounds = FRect(GetComponentPosition(), Size.X * RelativeScale.X, Size.Y * RelativeScale.Y);
}
