#pragma once

#include "TypeDefine.h"

// This:: or Super:: 를 사용하기 위해 작성

// 클래스 선언 상단에 작성해야 함.
/*
    CLASS(MyClass, BaseClass)
	class MyClass : public BaseClass { ... }

	CLASS(MyClass, )
	class MyClass { ... }
*/
#define CLASS(_ThisClass, _BaseClass)        \
typedef class _ThisClass _This_##_ThisClass; \
typedef class _BaseClass _Base_##_ThisClass; 
											 
// 클래스나 인터페이스 몸체 첫 줄에 작성해야 함.
/*
    
    CLASS(MyClass, BaseClass)
	class MyClass : public BaseClass 
	{
		USE_CLASS(MyClass);
		...
	}

	interface IMyInterface 
	{
		USE_INTERFACE(IMyInterface);
		...
	}
*/
#define USE_CLASS(_ThisClass)                \
typedef _This_##_ThisClass This;             \
typedef _Base_##_ThisClass Super

#define USE_INTERFACE(_ThisInterfaceClass)   \
FORCEINLINE virtual ~_ThisInterfaceClass() {}


