#include "PlayerHUD.h"

#include "Base/Component/Scene/Render/UI/UISpriteRenderer/UISpriteRendererComponent.h"

void CPlayerHUD::Initialize()
{
	Super::Initialize();

	Size = FVector(100.0f);

	Anchor = Pivot = FVector::ZeroVector();

	Name = TEXT("PlayerHUD");
	
	HpBackground = AddUIComponent<CUISpriteRendererComponent>();
	HpBackground->SetAnchorPivotPositionScale(FVector(0.0f), FVector(0.0f), 
		FVector(10.0f, 24.0f), FVector(2.0f));

	HpBackground->SetDrawSpriteInfo(FSpriteInfo::MakeSpriteInfo(
		TEXT("Resources/CharacterHUD/T_BarBackground.bmp"), 
		ESpriteDrawType::UseTransparentBlt, 
		FVector::ZeroVector()));

	HpForeground = AddUIComponent<CUISpriteRendererComponent>();
	HpForeground->SetAnchorPivotPositionScale(0.0f, 0.0f, FVector(14.0f, 28.0f), 2.0f);
	HpForeground->SetDrawSpriteInfo(FSpriteInfo::MakeSpriteInfo(
		TEXT("Resources/CharacterHUD/T_HpForeground.bmp"),
		ESpriteDrawType::UseTransparentBlt,
		0.0f));
}

void CPlayerHUD::SetHp(float hp)
{
	hp = FMath::Clamp(hp, 0.0f, 1.0f);

	float max = HpForeground->DrawSpriteInfo->GetLoadedSpriteImageSize().X;
	HpForeground->DrawSpriteInfo->SpriteImageSize.X = (max * hp);
}
