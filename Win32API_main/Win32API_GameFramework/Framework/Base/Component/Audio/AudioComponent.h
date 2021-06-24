#pragma once
#include <fmod_common.h>

#include "Framework/Base/Component/Component.h"

#ifndef AUDIO_DEFINES
#define AUDIO_DEFINES

#define AUDIO_VOLUME_MIN 0.1f
#define AUDIO_VOLUME_MAX 0.1f
#endif AUDIO_DEFINES

class CAudioComponent :
    public CComponent
{
private:
    FMOD_SOUND* Sound;
    FMOD_CHANNEL* Channel;
    float Volume; // 0.0f ~ 1.0f
    FMOD_BOOL bIsPlaying;
    bool bIsPause;

public:
    CAudioComponent();

public:
    virtual void Tick(float dt) override;
    virtual void Release() override;

    void InitializeAudioComponent(string path, bool bLoop = false);

    void Play();

    void Pause();    

    void Stop();

    void SetVolume(float volume);
};

