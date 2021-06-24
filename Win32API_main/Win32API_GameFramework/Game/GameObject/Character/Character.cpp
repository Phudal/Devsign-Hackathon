#include "Character.h"

#include "Framework/Single/InputManager/InputManager.h"
#include "Framework/Bitmap/Bitmap.h"

#include "Game/Components/Movement/MovementComponent.h"

void CCharacter::Initialize()
{
	super::Initialize();

	Movement = AddComponent<CMovementComponent>();

}
