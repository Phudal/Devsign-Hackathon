#include "Rect.h"

FRect::FRect()
{
    Min = Max = FVector::ZeroVector();
}

FRect::FRect(float left, float top, float right, float bottom) : 
    FRect(FVector(left, top), FVector(right, bottom)) { }

FRect::FRect(FVector min, FVector max)
{
    Min = min;
    Max = max;
}

FRect::FRect(FVector center, float width, float height)
{
    FVector halfSize(width * 0.5f, height * 0.5f);
    Min = center - halfSize;
    Max = center + halfSize;
}

tstring FRect::ToString() const
{
    tstring returnValue;

    returnValue += TEXT("LT : (") + to_tstring(Min.X) + TEXT(", ") + to_tstring(Min.Y) + TEXT(")");
    returnValue += TEXT("  RB : (") + to_tstring(Max.X) + TEXT(", ") + to_tstring(Max.Y) + TEXT(")");

    return returnValue;
}
