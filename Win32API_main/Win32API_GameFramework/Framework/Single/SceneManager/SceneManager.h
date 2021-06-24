#pragma once
#include "Framework/Single/ManagerClassBase/ManagerClassBase.h"
#include "Framework/Base/Scene/Scene.h"

class CSceneManager final :
    public CManagerClassBase<CSceneManager>
{
private :
    CScene* CurrentScene;

    CScene* NextScene;

public :
    CSceneManager();

public :
    virtual void ReleaseManagerClass() override;

public :
    void Tick(float deltaSeconds);
    void Render(HDC hdc);

public :
    template<typename SceneType>
    void LoadScene()
    {
        if (!IsA<CScene, SceneType>())
        {
            LOG(ToTString(typeid(SceneType).name()) << 
                TEXT(" 형식은 CScene 형식과 상속 관계가 아닌 형식입니다."));
            return;
        }

        CObject::DeleteObject(NextScene);

        NextScene = NewObject<SceneType>();
    }

    FORCEINLINE CScene* GetActiveScene() const
    { return CurrentScene; }
};

