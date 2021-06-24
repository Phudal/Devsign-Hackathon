#pragma once

/* ~~ ENGINE DEFINES ~~*/
// 고정 FPS 설정
#define TARGET_FPS		60

// GameInstance 클래스를 정의합니다.
/// - GameInstance 클래스의 파생 클래스가 존재한다면 이곳을 변경해야 합니다.
#define DEF_GAMEINSTANCECLASS CGameInstance

extern class DEF_GAMEINSTANCECLASS* GameInstance;




/* ~~ GAME DEFINE ~~ */
// 처음에 실행될 씬 설정
// - 추가된 Scene Header 는 SceneManager.cpp 에 추가합니다.
//#define DEF_SCENE class CScene
#define DEF_SCENE class CGameScene
//#define DEF_SCENE class CMapEditerScene

