#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CCharacter abstract :
    public CGameObject
{
protected :
    class CMovementComponent* Movement;

public :
    virtual void Initialize() override;

};

