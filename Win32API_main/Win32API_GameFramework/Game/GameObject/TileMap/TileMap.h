#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CTileMap :
    public CGameObject
{
private:
    struct FTileMapInfo* TileMapData;

    int32 TileMapScale;    
    
    FVector MapSize;

    vector<class CTileMapRendererComponent*> TileMapRenderers;

    bool bUseUpdateTileDrawState;

    FThread* UpdateTileDrawStateThread;

public:
    virtual void Initialize() override;
    virtual void Release() override;

private:
    void MakeTileMapInfo(string mapCode);

    void UpdateMapSize();

public :
    FVector GetTileLT(int32 tileIndexX, int32 tileIndexY);
    FVector GetTileRB(int32 tileIndexX, int32 tileIndexY);

    bool IsBlockingTile(int32 tileIndexX, int32 tileIndexY);

public:
    FORCEINLINE void SetTileMap(string mapCode, int32 tileMapScale = 1)
    {
        MakeTileMapInfo(mapCode);
        SetTileMapScale(tileMapScale);
    }

    FORCEINLINE struct FTileMapInfo* GetTileMapData() const
    { return TileMapData; }

    FORCEINLINE const FVector& GetMapSize() const
    {
        return MapSize;
    }

    void SetTileMapXY(int32 sizeX, int32 sizeY);

    void SetTileMapScale(int32 scale);

    void MakeTileMap();


};

