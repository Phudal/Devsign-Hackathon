#pragma once
#include "Framework/Base/Object/Object.h"
#include "Framework/Struct/Vector/Vector.h"

struct FRect final :
    public CObject
{
public :
    FVector Min, Max;

public :
    FRect();
    FRect(float left, float top, float right, float bottom);
    FRect(FVector min, FVector max);
    FRect(FVector center, float width, float height);

public :
    virtual tstring ToString() const override;

    FORCEINLINE float GetLeft() const       { return Min.X; }
    FORCEINLINE float GetTop() const        { return Min.Y; }
    FORCEINLINE float GetRight() const      { return Max.X; }
    FORCEINLINE float GetBottom() const     { return Max.Y; }
    FORCEINLINE FVector GetCenter() const   { return ((Max - Min) * 0.5f) + Min; }
    FORCEINLINE FVector GetSize() const     { return Max - Min; }

    FORCEINLINE FVector GetBoundaryFromIntAxis(int32 x, int32 y) const
    {
        return FVector(
            ((x < 0) ? Min.X : Max.X),
            ((y < 0) ? Min.Y : Max.Y));
    }

};

