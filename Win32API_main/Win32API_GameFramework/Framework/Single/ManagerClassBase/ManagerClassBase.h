#pragma once

#include "Framework/Base/Object/Object.h"

#include "Framework/Interface/ManagerClass.h"

#include "Framework/Single/GameInstance/GameInstance.h"

template<typename ManagerClassType>
class CManagerClassBase abstract :
	public CObject,
	public IManagerClass
{
public :
	FORCEINLINE virtual void InitializeManagerClass() override { }
	FORCEINLINE virtual void ReleaseManagerClass() override { }

	FORCEINLINE static ManagerClassType* Instance()
	{
		static ManagerClassType* managerInstance = nullptr;

		return managerInstance = (managerInstance == nullptr) ?
			GameInstance->GetManagerClass<ManagerClassType>() :
			managerInstance;
	}
};
