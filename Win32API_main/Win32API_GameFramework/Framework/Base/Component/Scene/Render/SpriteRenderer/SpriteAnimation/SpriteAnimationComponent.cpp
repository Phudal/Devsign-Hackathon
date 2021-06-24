#include "SpriteAnimationComponent.h"

#include "Framework/Statics/GameplayStatics.h"

#include "Framework/Bitmap/Bitmap.h"

void CSpriteAnimationComponent::Initialize()
{
	super::Initialize();

	SpriteAnimation = nullptr;
	SpriteIndex = 0;
	LastSpriteChangedTime = 0.0f;
}

void CSpriteAnimationComponent::Tick(float dt)
{
	super::Tick(dt);

	LoopAnimation();
}

void CSpriteAnimationComponent::Release()
{
	DrawSpriteInfo = nullptr;

	for (auto iter = SpriteAnimInfos.begin(); iter != SpriteAnimInfos.end(); ++iter)
		CObject::DeleteObject(iter->second);
	SpriteAnimInfos.clear();

	super::Release();
}

void CSpriteAnimationComponent::FlipXY(bool flipX, bool flipY)
{
	if (SpriteAnimation == nullptr) return;

	for (auto iter = SpriteAnimation->SpriteInfos.begin(); 
		iter != SpriteAnimation->SpriteInfos.end(); 
		++iter)
	{
		(*iter)->GetLoadedBitmap()->bIsFlippedX = flipX;
		(*iter)->GetLoadedBitmap()->bIsFlippedY = flipY;
	}
}

void CSpriteAnimationComponent::LoopAnimation()
{
	if (SpriteAnimation == nullptr)
		return;
	else
	{
		auto spriteInfo = (*SpriteAnimation)[SpriteIndex];
		if (spriteInfo)
			DrawSpriteInfo = spriteInfo;

		if (CGameplayStatics::GetTime() - LastSpriteChangedTime >= SpriteAnimation->SpriteDelay)
		{
			LastSpriteChangedTime += SpriteAnimation->SpriteDelay;

			SpriteIndex = (SpriteIndex == SpriteAnimation->GetLastSpriteIndex()) ? 0 : ++SpriteIndex;
		}
	}
}

void CSpriteAnimationComponent::AddSpriteAnimation(
	tstring newAnimationName, 
	const vector<FSpriteInfo*>& spriteInfos, 
	float spriteDelay)
{
	if (SpriteAnimInfos.find(newAnimationName) != SpriteAnimInfos.end())
	{
		tstring title = TEXT("Error adding sprite animation!");
		tstring msg = TEXT("animation name = ") + newAnimationName;

		LOGF(TEXT("[Error] ") << title << TEXT(" : ") << msg);
		::MessageBox(Hwnd, msg.c_str(), title.c_str(), MB_OK | MB_ICONSTOP);

		return;
	}

	FSpriteAnimInfo* newSpriteAnimInfo = CObject::NewObject<FSpriteAnimInfo>();

	newSpriteAnimInfo->InitializeSpriteAnimInfo(spriteInfos, spriteDelay);

	SpriteAnimInfos.insert(make_pair(newAnimationName, newSpriteAnimInfo));
}

void CSpriteAnimationComponent::PlaySpriteAnimation(tstring animationName, int32 startIndex)
{
	if (animationName == STOP_ANIMATION)
	{
		SpriteAnimation = nullptr;
		return;
	}

	if (SpriteAnimInfos.find(animationName) == SpriteAnimInfos.end())
	{
		LOGF(TEXT("애니메이션 이름을 찾을 수 없습니다. AnimationName = ") << animationName);
		return;
	}

	if (SpriteAnimationName == animationName) return;

	SpriteAnimationName = animationName;

	SpriteAnimation = SpriteAnimInfos[animationName];

	SpriteIndex = startIndex;

	SpriteIndex = FMath::Clamp(SpriteIndex, 0, SpriteAnimation->GetLastSpriteIndex());

	LastSpriteChangedTime = CGameplayStatics::GetTime();
}
