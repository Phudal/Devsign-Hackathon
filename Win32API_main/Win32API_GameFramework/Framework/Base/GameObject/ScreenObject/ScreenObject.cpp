#include "ScreenObject.h"

#include "Base/GameObject/UIObject/UIObject.h"

CScreenObject::CScreenObject()
{
	ScreenBounds = FRect(FVector::ZeroVector(), FVector::ScreenSize());
}

void CScreenObject::AddUIObject(CUIObject* newUIObject)
{
	UIObjects.push_back(newUIObject);
	newUIObject->ScreenObject = this;
	newUIObject->OnUIObjectCreated();
}

void CScreenObject::DestroyUIObject(CUIObject* uiObject)
{
	UIObjects.remove(uiObject);
	OwnerScene->Destroy(uiObject);
}
