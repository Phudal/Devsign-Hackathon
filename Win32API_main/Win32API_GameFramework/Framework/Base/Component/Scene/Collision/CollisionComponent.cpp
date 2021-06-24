#include "CollisionComponent.h"

void CCollisionComponent::OnOverlapped(CCollisionComponent* other)
{
	if (OverlapEvents.size() > 0)
	{
		for (auto overlapEvent : OverlapEvents)
			overlapEvent(other);
	}

}

void CCollisionComponent::Tick(float dt)
{
	super::Tick(dt);

	UpdateBounds();
}
