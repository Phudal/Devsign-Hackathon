#pragma once

#include "Include/DefaultInclude.h"
#include "Struct/Rect/Rect.h"
#include "Struct/Vector/Vector.h"

interface IUIComponent
{
	USE_INTERFACE(IUIComponent);


	virtual void UpdateUIComponentBoundary() PURE;

	virtual void SetPivot(FVector newPivot) PURE;
	virtual FVector GetPivot() const PURE;
	
	virtual void SetAnchor(FVector newAnchor) PURE;
	virtual FVector GetAnchor() const PURE;

	virtual FRect GetBounds() const PURE;
};