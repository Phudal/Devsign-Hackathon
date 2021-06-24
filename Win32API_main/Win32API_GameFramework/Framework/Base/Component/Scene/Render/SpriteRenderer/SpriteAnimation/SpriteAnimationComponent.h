#pragma once
#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteRendererComponent.h"
#include "Framework/Struct/SpriteAnimInfo/SpriteAnimInfo.h"

#ifndef STOP_ANIMATION
#define STOP_ANIMATION      TEXT("NONE")
#endif

class CSpriteAnimationComponent :
    public CSpriteRendererComponent
{
private :
    tstring SpriteAnimationName;

    map<tstring, FSpriteAnimInfo*> SpriteAnimInfos;

    FSpriteAnimInfo* SpriteAnimation;

    int32 SpriteIndex;

    float LastSpriteChangedTime;

public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;
    virtual void Release() override;

    virtual void FlipXY(bool flipX, bool flipY) override;

private :
    void LoopAnimation();

public :
    void AddSpriteAnimation(
        tstring newAnimationName,
        const vector<FSpriteInfo*>& spriteInfos,
        float spriteDelay);

    void PlaySpriteAnimation(tstring animationName, int32 startIndex = 0);

    FORCEINLINE virtual void SetDrawSpriteInfo(FSpriteInfo* newSpriteInfo) override
    { DrawSpriteInfo = newSpriteInfo; }


};

