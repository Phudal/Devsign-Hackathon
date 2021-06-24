#pragma once

#include "Include/DefaultInclude.h"


interface IObjectPoolable
{	
	virtual void SetCanRecyclable(bool bCanRecyclable) PURE;
	virtual bool GetCanRecyclable() const PURE;
	
	virtual void OnRecycleStarted() PURE;

	virtual ~IObjectPoolable() {}
};