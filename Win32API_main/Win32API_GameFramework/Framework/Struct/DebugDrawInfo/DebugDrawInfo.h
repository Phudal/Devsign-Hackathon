#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Enum/DebugDrawType.h"
#include "Framework/Struct/Vector/Vector.h"

struct FDebugDrawInfo final : 
	public CObject
{
public :
	EDebugDrawType DebugDrawType;

	FVector Vec1;

	FVector Vec2;

	float DrawStartTime;

	float Duration;

	COLORREF Color;

	HGDIOBJ HBrush;
	HGDIOBJ HPen;

	bool bFill;

	function<void(HDC)> FnDraw;

public :
	virtual void Initialize() override;
	virtual void Release() override;

	void InitializeDebugDrawInfo(
		EDebugDrawType debugDrawType, 
		FVector vec1, 
		FVector vec2, 
		COLORREF color,
		float duration,
		bool bFill);

	void Draw(HDC hdc) const;

};