#pragma once
#include "Framework/Base/Component/Scene/Render/SpriteRenderer/SpriteAnimation/SpriteAnimationComponent.h"


class CPlayerSpriteAnimationComponent final :
    public CSpriteAnimationComponent
{

public :
    virtual void Initialize() override;
    virtual void Tick(float dt) override;

private:
    void AnimControl();

};

