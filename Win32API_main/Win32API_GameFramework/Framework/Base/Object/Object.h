#pragma once

#include "Include/DefaultInclude.h"

#define super __super

class CObject
{
public :
	CObject();
	FORCEINLINE virtual void Initialize() {}
	FORCEINLINE virtual void Release() {}
	virtual ~CObject();

public :
	virtual tstring ToString() const;

	template<typename ParentType, typename ChildType>
	FORCEINLINE static bool IsA(ChildType* childInstance)
	{ return (dynamic_cast<ParentType*>(childInstance) != nullptr); }

	template<typename ParentType, typename ChildType>
	FORCEINLINE static bool IsA()
	{ return is_base_of<ParentType, ChildType>(); }

	template<typename TargetType, typename T>
	FORCEINLINE static TargetType* Cast(T* instance)
	{ return dynamic_cast<TargetType*>(instance); }

	template<typename T>
	FORCEINLINE static T* NewObject()
	{
		T* newObject = new T();
		newObject->Initialize();

		return newObject;
	}

	template<typename T>
	FORCEINLINE static void DeleteObject(T*& object)
	{
		if (object == nullptr) return;

		object->Release();
		delete object;
		object = nullptr;
	}

};



