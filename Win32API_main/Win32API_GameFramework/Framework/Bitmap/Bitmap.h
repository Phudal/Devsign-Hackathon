#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"
#include "Framework/Struct/BitmapInfo/BitmapInfo.h"

class CBitmap final :
    public CObject
{
private:
    static map<tstring, CBitmap*> LoadedBitmaps;

private :
    HDC Hdc, MemDC,
        XFlippedHDC, YFlippedHDC, XYFlippedHDC;

    HBITMAP Bmp, OldBmp,
        XFlippedBmp, YFlippedBmp, XYFlippedBmp,
        OldXFlippedBmp, OldYFlippedBmp, OldXYFlippedBmp;

    FVector Size;

    FBitmapInfo* BitmapInfo;

    bool bUseFlippedBmp;

public :
    bool bIsFlippedX, bIsFlippedY;


public :
    CBitmap();

public :
    static CBitmap* LoadBmp(CBitmap* bitmap, tstring path, bool bUseFlippedBmp = true, tstring key = TEXT("USE_PATH"));

public :
    static void ReleaseAllBmp();
    virtual void Release() override;

public :
    void FlipXY(bool flipX, bool flipY);

    FORCEINLINE FVector GetSize() const
    { return Size; }

    FORCEINLINE HDC GetDC() const
    {
        if (!bUseFlippedBmp)                    return MemDC;

        if (bIsFlippedX && bIsFlippedY)         return XYFlippedHDC;
        else if (!bIsFlippedX && !bIsFlippedY)  return MemDC;

        if (bIsFlippedX)                        return XFlippedHDC;
        else                                    return YFlippedHDC;
    }

    FORCEINLINE bool IsValid() const
    { return Bmp != NULL; }
};

