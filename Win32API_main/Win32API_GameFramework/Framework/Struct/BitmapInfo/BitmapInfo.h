#pragma once
#include "Framework/Base/Object/Object.h"

struct FBitmapInfo :
    public CObject
{
public :
    COLORREF** PixelColors;

    int32 PixelXCount;
    int32 PixelYCount;

public :
    FBitmapInfo();

public :
    void InitializeBitmapInfo(COLORREF** pixelColors, int32 pixelXCount, int32 pixelYCount);

public :
    virtual void Release() override;

};

