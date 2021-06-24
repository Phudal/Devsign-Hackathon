#include "TileMapInfo.h"

void FTileMapInfo::Initialize()
{
	super::Initialize();

	TileMapXCount = TileMapYCount = 0;
	TileMapData = CollisionData = nullptr;
}

void FTileMapInfo::Release()
{
	if (TileMapData != nullptr)
	{
		for (int32 y = 0; y < TileMapYCount; ++y)
			delete[] TileMapData[y];
		delete TileMapData;
	}

	if (CollisionData != nullptr)
	{
		for (int32 y = 0; y < TileMapYCount; ++y)
			delete[] CollisionData[y];
		delete CollisionData;
	}
	TileMapData = CollisionData = nullptr;
	
	super::Release();
}

void FTileMapInfo::InitializeTileMap(string mapCode)
{
	ifstream inputFileStream;
	inputFileStream.open(("Resources/MapData/" + mapCode + ".txt").c_str());

	if (!inputFileStream.is_open())
	{
		tstring msg = TEXT("맵 파일을 불러오지 못했습니다/ \n 맵코드 : ") + ToTString(mapCode);
		MessageBox(Hwnd, msg.c_str(), TEXT("Error"), MB_OK | MB_ICONSTOP);
			return;
	}
	
	inputFileStream >> TileMapXCount;
	inputFileStream >> TileMapYCount;

	if (TileMapXCount == 0 || TileMapYCount == 0)
	{
		LOG(TEXT("TileMapXCount/TileMapYCount is zero"));
		return;		
	}
		
	TileMapData = new int32 * [TileMapYCount];
	for (int32 y = 0; y < TileMapYCount; ++y)
	{
		TileMapData[y] = new int32[TileMapXCount];
		for (int32 x = 0; x < TileMapXCount; ++x)
		{
			inputFileStream >> TileMapData[y][x];
		}
	}

	CollisionData = new int32 * [TileMapYCount];
	for (int32 y = 0; y < TileMapYCount; ++y)
	{
		CollisionData[y] = new int32[TileMapXCount];
		for (int32 x = 0; x < TileMapXCount; ++x)
		{
			inputFileStream >> CollisionData[y][x];
		}
	}
}
	
	
