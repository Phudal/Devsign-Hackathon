#pragma once
#include "Game/GameObject/Character/Character.h"

class CPlayerCharacter final :
    public CCharacter
{
private :
    class CSpriteAnimationComponent* SpriteAnimation;
    class CPlayerCharacterMovementHelperComponent* MovementHelper;

    class CPlayerHUD* PlayerHUD;

    FVector InputAxis;

    float MaxHp;
    float Hp;

public :
    virtual void Initialize() override;

    virtual void Tick(float dt) override;
    virtual void Release() override;

private :
    void InputKey(float dt);

public :
    FORCEINLINE class CMovementComponent* GetMovement() const
    { return Movement; }

    FORCEINLINE class CPlayerCharacterMovementHelperComponent* GetMovementHelper() const
    { return MovementHelper; }

    FORCEINLINE FVector GetInputAxis() const
    { return InputAxis; }
};

