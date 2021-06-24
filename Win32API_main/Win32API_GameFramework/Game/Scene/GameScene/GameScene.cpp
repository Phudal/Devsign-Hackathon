#include "GameScene.h"
#include "Game/GameObject/Character/PlayerCharacter/PlayerCharacter.h"
#include "Game/GameObject/Audio/AudioObject.h"
#include "Game/GameObject/TileMap/TileMap.h"

void CGameScene::Initialize()
{
	super::Initialize();
	
	
	AudioObject = NewGameObject<CAudioObject>(TEXT("AudioObject"));
	AudioObject->CreateAudio("Resources/Audio/Pleasant_Porridge.mp3");

	TileMap = NewGameObject<CTileMap>(TEXT("TileMap"));
	TileMap->SetTileMap("000000", 3);


	NewGameObject<CPlayerCharacter>(TEXT("PlayerCharacter"));
}
