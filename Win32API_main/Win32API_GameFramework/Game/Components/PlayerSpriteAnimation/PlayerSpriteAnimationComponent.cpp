#include "PlayerSpriteAnimationComponent.h"

#include "Game/GameObject/Character/PlayerCharacter/PlayerCharacter.h"
#include "Game/Components/PlayerCharacterMovementHelper/PlayerCharacterMovementHelperComponent.h"
#include "Game/Components/Movement/MovementComponent.h"
#include "Framework/Enum/Direction.h"

void CPlayerSpriteAnimationComponent::Initialize()
{
	super::Initialize();	

#pragma region IDLE ANIMATION

	vector<FSpriteInfo*> idleSpriteInfos;
	vector<tstring> idleSpritePaths = {
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 1.bmp"),
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 2.bmp"),
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 3.bmp"),
		TEXT("Resources/PlayerCharacter/IDLE/IDLE 4.bmp")
	};

	FSpriteInfo::MakeSpriteInfos(
		idleSpriteInfos, idleSpritePaths, ESpriteDrawType::UseTransparentBlt, FVector(0.5f, 0.7f));
	AddSpriteAnimation(TEXT("Idle"), idleSpriteInfos, 0.3f);

#pragma endregion


#pragma region WALK ANIMATION

	vector<FSpriteInfo*> walkSpriteInfos;
	vector<tstring> walkSpritePaths = {
		TEXT("Resources/PlayerCharacter/WALK/WALK 1.bmp"),
		TEXT("Resources/PlayerCharacter/WALK/WALK 2.bmp"),
		TEXT("Resources/PlayerCharacter/WALK/WALK 3.bmp"),
		TEXT("Resources/PlayerCharacter/WALK/WALK 4.bmp")
	};

	FSpriteInfo::MakeSpriteInfos(
		walkSpriteInfos, walkSpritePaths, ESpriteDrawType::UseTransparentBlt, FVector(0.5f, 0.7f));
	AddSpriteAnimation(TEXT("Walk"), walkSpriteInfos, 0.2f);
		


#pragma endregion

	PlaySpriteAnimation(TEXT("Idle"));

	RelativeScale = FVector::OneVector() * 0.3f;
}

void CPlayerSpriteAnimationComponent::Tick(float dt)
{
	super::Tick(dt);

	AnimControl();
}

void CPlayerSpriteAnimationComponent::AnimControl()
{	
	CPlayerCharacter* playerCharacter = Cast<CPlayerCharacter>(Owner);

	if (playerCharacter == nullptr) return;


	tstring animNameToPlay = STOP_ANIMATION;

	float speed = playerCharacter->GetMovement()->Velocity.Length();

	animNameToPlay = (speed < 0.1f) ? TEXT("Idle") : TEXT("Walk");

	FlipXY(playerCharacter->GetMovementHelper()->GetLookDirection() == EDirection::Left, false);

	PlaySpriteAnimation(animNameToPlay);
}
