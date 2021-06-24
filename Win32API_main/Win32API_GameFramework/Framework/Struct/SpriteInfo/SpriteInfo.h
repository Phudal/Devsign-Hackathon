#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"
#include "Framework/Enum/SpriteDrawType.h"

#ifndef USE_LOADED_SIZE
#define USE_LOADED_SIZE FVector(-1.0f, -1.0f)
#endif


struct FSpriteInfo :
    public CObject
{
private :
    class CBitmap* LoadedBitmap;

    FVector LoadedSpriteImageSize;

public :
    ESpriteDrawType SpriteDrawType;

    COLORREF CRTransparent;

    DWORD DWRop;

    FVector CropLT;

    FVector SpriteImageSize;

    FVector DrawPivot;

public :
    FSpriteInfo();

    void InitializeSpriteInfo(
        tstring imagePath,
        ESpriteDrawType spriteDrawType,
        FVector imageSize = USE_LOADED_SIZE,
        bool bUseFlip = true);

public :
    virtual void Release() override;

public :
    static void MakeSpriteInfos(
        vector<FSpriteInfo*>& outSpriteInfos,
        const vector<tstring>& imagePaths,
        ESpriteDrawType spriteDrawType,
        FVector pivot = FVector(0.5f, 0.5f),
        COLORREF crTransparent = RGB(255, 0, 255),
        DWORD dwRop = SRCCOPY);

    static FSpriteInfo* MakeSpriteInfo(
        tstring imagePath,
        ESpriteDrawType spriteDrawType,
        FVector pivot = FVector(0.5f, 0.5f));

public :
    HDC GetDC() const;

    FORCEINLINE FVector GetLoadedSpriteImageSize() const
    { return LoadedSpriteImageSize; }

    FORCEINLINE class CBitmap* GetLoadedBitmap() const
    { return LoadedBitmap; }

    bool IsValid() const;

};

