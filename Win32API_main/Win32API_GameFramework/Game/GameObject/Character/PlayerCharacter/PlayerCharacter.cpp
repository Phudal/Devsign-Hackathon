#include "PlayerCharacter.h"

#include "Single/InputManager/InputManager.h"

#include "Components/Movement/MovementComponent.h"
#include "GameObject/TileMap/TileMap.h"

#include "Components/PlayerSpriteAnimation/PlayerSpriteAnimationComponent.h"
#include "Components/PlayerCharacterMovementHelper/PlayerCharacterMovementHelperComponent.h"

#include "Base/GameObject/ScreenObject/ScreenObject.h"

#include "GameObject/UIObject/PlayerHUD/PlayerHUD.h"
#include "Scene/GameScene/GameScene.h"

void CPlayerCharacter::Initialize()
{
	super::Initialize();
	Position = FVector::ScreenCenter();
	Movement->MaxSpeed = 300.0f;
	Movement->BrakingForce = 1000.0f;

	MaxHp = Hp = 1000.0f;

	SpriteAnimation = AddComponent<CPlayerSpriteAnimationComponent>();
	MovementHelper = AddComponent<CPlayerCharacterMovementHelperComponent>();

	MovementHelper->SetTileMap(Cast<CGameScene>(OwnerScene)->GetTileMap());

	OwnerScene->GetScreen()->CreateUIObject<CUIObject>();

	PlayerHUD = OwnerScene->GetScreen()->CreateUIObject<CPlayerHUD>();
}


void CPlayerCharacter::Tick(float dt)
{
	super::Tick(dt);

	InputKey(dt);

	OwnerScene->CameraPosition = FVector::Lerp(
		OwnerScene->CameraPosition, Position, 3.0f * dt);	
}

void CPlayerCharacter::Release()
{
	super::Release();
}

void CPlayerCharacter::InputKey(float dt)
{
	InputAxis = FVector(
		CInput::GetAxis(TEXT("Horizontal")),
		CInput::GetAxis(TEXT("Vertical")));

	Movement->AddMovement(FVector::RightVector() * InputAxis.X);
	
	Movement->AddMovement(FVector::DownVector() * InputAxis.Y);

	if (CInput::GetKeyDown(TEXT("Space")))
	{
		Movement->AddImpulse(FVector::RightVector() * 1000.0f);
	}

	Hp += InputAxis.X * 5;
	Hp = FMath::Clamp(Hp, 0.0f, MaxHp);
	PlayerHUD->SetHp(Hp / MaxHp);
}

