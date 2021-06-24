#include "SpriteRendererComponent.h"

#include "Base/GameObject/GameObject.h"

#include "Framework/Bitmap/Bitmap.h"

CSpriteRendererComponent::CSpriteRendererComponent()
{
	bUseCameraPosition = true;
	bUseRender = true;
	DrawSpriteInfo = nullptr;
	bIsFlippedX = bIsFlippedY = false;
}

void CSpriteRendererComponent::Render(HDC hdc)
{
	super::Render(hdc);

	if (DrawSpriteInfo == nullptr) return;
	if (!DrawSpriteInfo->IsValid()) return;
	if (DrawSpriteInfo->SpriteDrawType == ESpriteDrawType::Hide) return;

	DrawSpriteImageSize = FVector(
		DrawSpriteInfo->SpriteImageSize.X * RelativeScale.X,
		DrawSpriteInfo->SpriteImageSize.Y * RelativeScale.Y);

	FVector ltOfPivotRectSize = FVector(
		DrawSpriteImageSize.X * DrawSpriteInfo->DrawPivot.X,
		DrawSpriteImageSize.Y * DrawSpriteInfo->DrawPivot.Y);

	DrawStartLT = GetComponentPosition() - ltOfPivotRectSize;

	DrawStartLT = ToRenderPosition(DrawStartLT);

	switch (DrawSpriteInfo->SpriteDrawType)
	{
		case ESpriteDrawType::UseTransparentBlt :
		{
			if (Owner->Name == TEXT("PlayerHUD"))
			{
			}

			TransparentBlt(hdc,
				DrawStartLT.X, DrawStartLT.Y,
				DrawSpriteImageSize.X, DrawSpriteImageSize.Y,
				DrawSpriteInfo->GetDC(),
				DrawSpriteInfo->CropLT.X, DrawSpriteInfo->CropLT.Y,
				DrawSpriteInfo->SpriteImageSize.X, DrawSpriteInfo->SpriteImageSize.Y,
				DrawSpriteInfo->CRTransparent);
			break;
		}
		case ESpriteDrawType::UseStretchBlt :
		{
			StretchBlt(hdc,
				DrawStartLT.X, DrawStartLT.Y,
				DrawSpriteImageSize.X, DrawSpriteImageSize.Y,
				DrawSpriteInfo->GetDC(),
				DrawSpriteInfo->CropLT.X, DrawSpriteInfo->CropLT.Y,
				DrawSpriteInfo->SpriteImageSize.X, DrawSpriteInfo->SpriteImageSize.Y,
				DrawSpriteInfo->DWRop);

			break;
		}

	}


}

void CSpriteRendererComponent::Release()
{
	if (DrawSpriteInfo)
		CObject::DeleteObject(DrawSpriteInfo);

	Super::Release();
}

void CSpriteRendererComponent::FlipXY(bool flipX, bool flipY)
{
	if (!DrawSpriteInfo) return;
	if (!DrawSpriteInfo->IsValid()) return;

	bIsFlippedX = DrawSpriteInfo->GetLoadedBitmap()->bIsFlippedX = flipX;
	bIsFlippedY = DrawSpriteInfo->GetLoadedBitmap()->bIsFlippedY = flipY;

}

void CSpriteRendererComponent::SetDrawSpriteInfo(FSpriteInfo* newSpriteInfo)
{
	if (DrawSpriteInfo)
		CObject::DeleteObject(DrawSpriteInfo);

	DrawSpriteInfo = newSpriteInfo;

	if (DrawSpriteInfo)
		DrawSpriteImageSize = DrawSpriteInfo->SpriteImageSize * RelativeScale;
}
