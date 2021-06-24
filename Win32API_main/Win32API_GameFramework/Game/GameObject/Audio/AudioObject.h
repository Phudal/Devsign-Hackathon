#pragma once
#include "Framework/Base/GameObject/GameObject.h"

class CAudioObject :
    public CGameObject
{
private:
    list<class CAudioComponent*> AudioComponents;

public:
    class CAudioComponent* CreateAudio(string path, bool bLoop = false);
};

