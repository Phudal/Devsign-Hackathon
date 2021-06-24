#include "CollisionManager.h"

#include "Framework/Base/GameObject/GameObject.h"

#include "Framework/Base/Component/Scene/Collision/RectCollision/RectCollisionComponent.h"
#include "Framework/Base/Component/Scene/Collision/CircleCollision/CircleCollisionComponent.h"


bool CCollisionManager::DoCollisionTestCircleToCircle(
	CCollisionComponent* circle1, CCollisionComponent* circle2)
{
	auto circleCollision1 = Cast<CCircleCollisionComponent>(circle1);
	auto circleCollision2 = Cast<CCircleCollisionComponent>(circle2);

	float distance = FVector::Distance(
		circleCollision1->GetBounds().GetCenter(), circleCollision2->GetBounds().GetCenter());

	float radius1 = circleCollision1->GetRadius();

	float radius2 = circleCollision2->GetRadius();

	return distance < (radius1 + radius2);
}

bool CCollisionManager::DoCollisionTestRectToRect(CCollisionComponent* rect1, CCollisionComponent* rect2)
{
	auto rectCollision1 = Cast<CRectCollisionComponent>(rect1);
	auto rectCollision2 = Cast<CRectCollisionComponent>(rect2);


	if (rectCollision1->GetBounds().GetLeft() > rectCollision2->GetBounds().GetRight()) return false;
	if (rectCollision1->GetBounds().GetRight() < rectCollision2->GetBounds().GetLeft()) return false;
	if (rectCollision1->GetBounds().GetTop() > rectCollision2->GetBounds().GetBottom()) return false;
	if (rectCollision1->GetBounds().GetBottom() < rectCollision2->GetBounds().GetTop()) return false;

	return true;
}

bool CCollisionManager::DoCollisionTestRectToCircle(CCollisionComponent* rect, CCollisionComponent* circle)
{
	auto* rectCollision = Cast<CRectCollisionComponent>(rect);
	auto* circleCollision = Cast<CCircleCollisionComponent>(circle);

	FVector halfRect = rectCollision->GetBounds().Max - rectCollision->GetBounds().Min;

	float l = sqrt(pow(halfRect.X, 2.0) + pow(halfRect.Y, 2.0f));

	float centerDistance = FVector::Distance(
		rectCollision->GetBounds().GetCenter(), 
		circleCollision->GetBounds().GetCenter());

	if ((circleCollision->GetRadius() + l) > centerDistance) return false;

	FVector circleCenter = circleCollision->GetBounds().GetCenter();

	if (FMath::IsIn(circleCenter.X, rectCollision->GetBounds().GetLeft(), rectCollision->GetBounds().GetRight()) ||
		FMath::IsIn(circleCenter.Y, rectCollision->GetBounds().GetTop(), rectCollision->GetBounds().GetBottom()))
	{
		FRect expansionRect = rectCollision->GetBounds();
		expansionRect.Min -= FVector::OneVector() * circleCollision->GetRadius();
		expansionRect.Max += FVector::OneVector() * circleCollision->GetRadius();

		if (circleCenter.X < expansionRect.GetLeft()) return false;
		else if (circleCenter.X > expansionRect.GetRight()) return false;
		else if (circleCenter.Y < expansionRect.GetTop()) return false;
		else if (circleCenter.Y > expansionRect.GetBottom()) return false;

		return true;
	}


	FVector rectCollisionSize = rectCollision->GetBounds().Max - rectCollision->GetBounds().Min;

	FVector rectCollisionPoints[4] =
	{
		rectCollision->GetBounds().Min,
		rectCollision->GetBounds().Min + FVector(0.0f, rectCollisionSize.Y),
		rectCollision->GetBounds().Max - FVector(0.0f, rectCollisionSize.Y),
		rectCollision->GetBounds().Max
	};

	for (FVector point : rectCollisionPoints)
	{
		if (FVector::Distance(circleCenter, point) <= circleCollision->GetRadius()) return true;
	}

	return false;
}

void CCollisionManager::DoCollisionTest()
{
	if (CreatedCollisions.size() != 0)
	{
		for (auto collision : CreatedCollisions)
			UsedCollisions.push_back(collision);
		CreatedCollisions.clear();
	}

	if (DestroyedCollisions.size() != 0)
	{
		for (auto collision : DestroyedCollisions)
			UsedCollisions.remove(collision);
		DestroyedCollisions.clear();
	}

	if (UsedCollisions.size() < 2) return;

	auto iter1 = UsedCollisions.begin();
	auto iter1Fin = --UsedCollisions.end();

	for (; iter1 != iter1Fin; ++iter1)
	{
		auto iter2 = iter1;
		++iter2;

		auto iter2Fin = UsedCollisions.end();

		if ((*iter1)->bBeDestroy) continue;
		if (!(*iter1)->bIsStarted) continue;

		for (; iter2 != iter2Fin; ++iter2)
		{
			if ((*iter1)->Owner->bBeDestroy || (*iter2)->Owner->bBeDestroy) continue;
			if ((*iter2)->bBeDestroy) continue;
			if (!(*iter2)->bIsStarted) continue;

			using namespace ECollisionType;

			switch ((*iter1)->GetCollisionType())
			{
			case Circle:
				if ((*iter2)->GetCollisionType() == Circle)
				{
					if (DoCollisionTestCircleToCircle((*iter1), (*iter2)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}

				else if ((*iter2)->GetCollisionType() == Circle)
				{
					if (DoCollisionTestRectToCircle((*iter2), (*iter1)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}
				break;

			case Rect :
				if ((*iter2)->GetCollisionType() == Rect)
				{
					if (DoCollisionTestRectToRect((*iter1), (*iter2)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}

				else if ((*iter2)->GetCollisionType() == Rect)
				{
					if (DoCollisionTestRectToCircle((*iter1), (*iter2)))
					{
						(*iter1)->OnOverlapped(*iter2);
						(*iter2)->OnOverlapped(*iter1);
					}
				}
				break;

			}

		}

	}
}

void CCollisionManager::RegisterCollision(CCollisionComponent* collision)
{
	CreatedCollisions.push_back(collision);
}

void CCollisionManager::UnRegisterCollision(CCollisionComponent* collision)
{
	DestroyedCollisions.push_back(collision);
}
