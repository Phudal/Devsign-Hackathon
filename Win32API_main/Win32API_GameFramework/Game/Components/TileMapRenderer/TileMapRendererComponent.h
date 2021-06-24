#pragma once
#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"
class CTileMapRendererComponent :
    public CSpriteRendererComponent
{
public:
    int32 TileIndexX;
    int32 TileIndexY;
    bool bIsBlockingTile;

private:
    FSpriteInfo* TileMapSpriteInfo;

public:
    virtual void Initialize() override;
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

public:
    void UpdatePosition();

    void UpdateDrawState();
};

