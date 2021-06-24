#include "UISpriteRendererComponent.h"
#include "Base/GameObject/ScreenObject/ScreenObject.h"
#include "Base/GameObject/UIObject/UIObject.h"

CUISpriteRendererComponent::CUISpriteRendererComponent()
{
	bUseCameraPosition = false;
	UIObject = nullptr;
	Pivot = Anchor = FVector(0.5f);
}

void CUISpriteRendererComponent::UpdateUIComponentBoundary()
{
	CUIObject* ownerUIObject = Cast<CUIObject>(Owner);
	if (ownerUIObject->ScreenObject == nullptr) return;
	if (DrawSpriteInfo == nullptr) return;
	if (!DrawSpriteInfo->IsValid()) return;

	FRect uiObjectBounds = ownerUIObject->GetBounds();

	FVector uiComponentAnchorPosition = uiObjectBounds.Min +
		(uiObjectBounds.GetSize() * GetAnchor());

	FVector uiComponentLT = uiComponentAnchorPosition + RelativePosition -
		(DrawSpriteImageSize * GetPivot());

	Bounds = FRect(uiComponentLT, uiComponentLT + DrawSpriteImageSize);
}
