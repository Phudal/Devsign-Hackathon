#include "CircleCollisionComponent.h"
#include "Framework/Base/GameObject/GameObject.h"

CCircleCollisionComponent::CCircleCollisionComponent()
{
	Radius = 0.0f;
	CollisionType = ECollisionType::Circle;
}

void CCircleCollisionComponent::UpdateBounds()
{
	Bounds = FRect(GetComponentPosition(), (Radius * RelativeScale.X) * 2.0f, (Radius * RelativeScale.Y) * 2.0f);
}

void CCircleCollisionComponent::SetRadius(float radius)
{
	Radius = radius;
	Bounds = FRect(GetComponentPosition(), (Radius * RelativeScale.X) * 2.0f, (Radius * RelativeScale.Y) * 2.0f);
}
