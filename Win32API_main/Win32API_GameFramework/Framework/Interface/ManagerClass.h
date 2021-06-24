#pragma once

#include "Include/DefaultInclude.h"

interface IManagerClass
{
	virtual void InitializeManagerClass() PURE;
	
	virtual void ReleaseManagerClass() PURE;

	virtual ~IManagerClass() {}
};