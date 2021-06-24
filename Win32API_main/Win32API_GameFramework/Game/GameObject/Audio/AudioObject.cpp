#include "AudioObject.h"
#include "Framework/Base/Component/Audio/AudioComponent.h"

CAudioComponent* CAudioObject::CreateAudio(string path, bool bLoop)
{
	CAudioComponent* newAudioComponent = AddComponent<CAudioComponent>();
	newAudioComponent->InitializeAudioComponent(path, bLoop);
	newAudioComponent->Play();

	AudioComponents.push_back(newAudioComponent);

	return newAudioComponent;
}
