#pragma once

#include "Framework/Base/Object/Object.h"

#include "Framework/Struct/SpriteInfo/SpriteInfo.h"


class FSpriteAnimInfo :
    public CObject
{
public :
    vector<FSpriteInfo*> SpriteInfos;

    float SpriteDelay;

public :
    FSpriteAnimInfo();

public :
    void InitializeSpriteAnimInfo(const vector<FSpriteInfo*> spriteInfos, float spriteDelay);

    virtual void Release() override;

public :
    FORCEINLINE FSpriteInfo* operator[](int32 index) const
    { return (SpriteInfos.size() == 0) ? nullptr : *(SpriteInfos.begin() + index); }

    FORCEINLINE int32 GetLastSpriteIndex() const
    { return SpriteInfos.size() - 1; }

};

