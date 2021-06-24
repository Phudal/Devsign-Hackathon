#pragma once

#include "Base/Object/Object.h"

struct FTileMapInfo :
	public CObject
{
public:

	int32 TileMapXCount;
	int32 TileMapYCount;

	int32** TileMapData;
	int32** CollisionData;

public:
	virtual void Initialize() override;
	virtual void Release() override;

public:
	virtual void InitializeTileMap(string mapCode);

	FORCEINLINE bool IsBlockingTile(int32 x, int32 y) const
	{
		if (CollisionData == nullptr)
			return false;
		return CollisionData[y][x] == 1;
	}
};