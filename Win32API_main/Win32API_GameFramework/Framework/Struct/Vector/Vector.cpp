#include "Vector.h"


FVector::FVector() : FVector(0.0f, 0.0f) { }
FVector::FVector(float xy) : FVector(xy, xy) { }
FVector::FVector(float x, float y) : X(x), Y(y) { }

float FVector::Distance(const FVector& v1, const FVector& v2)
{ return sqrt(pow(v2.X - v1.X, 2) + pow(v2.Y - v1.Y, 2)); }

FVector FVector::Direction(const FVector& from, const FVector& to)
{ return FVector((to.X - from.X), (to.Y - from.Y)).Normalized(); }

FVector FVector::Lerp(const FVector& a, const FVector& b, float t)
{
	return FVector(
		FMath::Lerp(a.X, b.X, t),
		FMath::Lerp(a.Y, b.Y, t));
}

float FVector::Length() const
{ return sqrt(pow(X, 2) + pow(Y, 2)); }

void FVector::Normalize()
{
	float length = Length();
	if (!FMath::Approximately(length, 0.0f))
	{
		X /= length;
		Y /= length;
	}
}

FVector FVector::Normalized() const
{
	float length = Length();
	return FMath::Approximately(length, 0.0f) ? 
		FVector::ZeroVector() :
		FVector(X / length, Y / length);
}

bool FVector::IsUnit(float errorTolerance) const
{
	return FMath::Abs(1.0f - SizeSquared()) < errorTolerance;
}

bool FVector::InWnd() const
{
	float wndWidth = WND_WIDTH;
	float wndHeight = WND_HEIGHT;

	if (!FMath::IsIn(X, 0.0f, wndWidth))
		return false;
	else if (!FMath::IsIn(Y, 0.0f, wndHeight))
		return false;
	else
		return true;
}

bool FVector::InWnd(const FVector& cameraPosition, FVector padding) const
{
	float wndHalfWidth = WND_WIDTH * 0.5f;
	float wndHalfHeight = WND_HEIGHT * 0.5f;

	if (!FMath::IsIn(X, 
		cameraPosition.X - wndHalfWidth - padding.X,
		cameraPosition.X + wndHalfWidth + padding.X))
		return false;

	else if (!FMath::IsIn(Y, 
		cameraPosition.Y - wndHalfHeight - padding.Y,
		cameraPosition.Y + wndHalfHeight + padding.Y))
		return false;
	else
		return true;
}


tstring FVector::ToString() const
{
	tstring str = TEXT("X = ");
	str += to_tstring(X);
	str += TEXT(", Y = ");
	str += to_tstring(Y);

	return str;
}

FVector FVector::VRand(float _min, float _max)
{ return FVector( FMath::RandRange(_min, _max), FMath::RandRange(_min, _max) ); }