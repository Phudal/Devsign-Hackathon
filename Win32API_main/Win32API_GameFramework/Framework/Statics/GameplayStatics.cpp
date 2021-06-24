#include "GameplayStatics.h"

float CGameplayStatics::GetTime()
{
    return (GetTickCount64() - GameStartTime) * 0.001f;
}

FVector CGameplayStatics::GetMousePosition(bool translated)
{
    POINT position;

    GetCursorPos(&position);
    if (!translated) return FVector(position.x, position.y);

    ScreenToClient(Hwnd, &position);
    return FVector(position.x, position.y);
}
