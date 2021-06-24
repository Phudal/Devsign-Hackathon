#include "RenderComponent.h"

#include "Framework/Base/GameObject/GameObject.h"
#include "Framework/Base/Scene/Scene.h"

CRenderComponent::CRenderComponent()
{
	bUseCameraPosition = false;
	bUseRender = true;
	SortingOrder = 0;
}

void CRenderComponent::SetSortingOrder(int32 order)
{
	SortingOrder = order;
	Owner->OwnerScene->bNeedSort = true;
}

CScene* CRenderComponent::GetActiveScene() const
{ return Owner->OwnerScene; }

FVector CRenderComponent::ToCameraPosition(const FVector& scenePosition) const
{
	return scenePosition - GetActiveScene()->CameraPosition + (FVector::ScreenSize() * 0.5f);
}

FVector CRenderComponent::ToRenderPosition(const FVector& scenePosition) const
{
	if (bUseCameraPosition) return ToCameraPosition(scenePosition);
	return scenePosition;
}
