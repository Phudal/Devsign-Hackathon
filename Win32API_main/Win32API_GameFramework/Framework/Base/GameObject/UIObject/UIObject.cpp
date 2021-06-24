#include "UIObject.h"

#include "Interface/UIComponent.h"

#include "Base/GameObject/ScreenObject/ScreenObject.h"

#include "Base/Scene/Scene.h"
#include "Bitmap/Bitmap.h"

void CUIObject::Initialize()
{
	Super::Initialize();

	ScreenObject = nullptr;
	Anchor = (Pivot = FVector::OneVector()) * 0.5f;
}

void CUIObject::OnUIObjectCreated()
{
	UpdateUIObjectBoundary();

	for (auto uiComponent : UIComponents)
		uiComponent->UpdateUIComponentBoundary();

}

void CUIObject::UpdateUIObjectBoundary()
{
	if (!ScreenObject) return;

	const FRect& screenBounds = ScreenObject->GetScreenBounds();

	FVector uiObjectAnchorPosition = screenBounds.Min +
		(screenBounds.GetSize() * GetAnchor());

	FVector uiObjectLT = uiObjectAnchorPosition + Position -
		(GetSize() * GetPivot());

	Bounds = FRect(uiObjectLT, uiObjectLT + GetSize());
}
