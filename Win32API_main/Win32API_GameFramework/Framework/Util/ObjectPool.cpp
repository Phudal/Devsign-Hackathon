#include "ObjectPool.h"

void CObjectPool::Release()
{
	super::Release();

	PoolObjects.clear();
}
