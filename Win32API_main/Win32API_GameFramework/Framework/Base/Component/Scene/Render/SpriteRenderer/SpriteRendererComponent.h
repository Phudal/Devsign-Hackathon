#pragma once
#include "FrameWork/Base/Component/Scene/Render/RenderComponent.h"
#include "Framework/Struct/SpriteInfo/SpriteInfo.h"

CLASS(CSpriteRendererComponent, CRenderComponent)
class CSpriteRendererComponent :
    public CRenderComponent
{
    USE_CLASS(CSpriteRendererComponent);

public :
    FSpriteInfo* DrawSpriteInfo;

protected :
    bool bIsFlippedX;
    bool bIsFlippedY;

    FVector DrawStartLT;

    FVector DrawSpriteImageSize;

public :
    CSpriteRendererComponent();

public :
    virtual void Render(HDC hdc) override;
    virtual void Release() override;

    virtual void FlipXY(bool flipX, bool flipY);

public :
    virtual void SetDrawSpriteInfo(FSpriteInfo* newSpriteInfo);
    

    FORCEINLINE void FlipX(bool flipX) { FlipXY(flipX, false); }
    FORCEINLINE void FlipY(bool flipY) { FlipXY(false, flipY); }

    FORCEINLINE bool IsFlippedX() const
    { return bIsFlippedX; }

    FORCEINLINE bool isFlippedY() const
    { return bIsFlippedY; }

};

