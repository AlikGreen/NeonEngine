#include "audioSystem.h"

#include "audioManager.h"
#include "components/audioSource.h"
#include "core/engine.h"
#include "core/sceneManager.h"
#include "core/components/transformComponent.h"
#include "neonECS/neonECS.h"

namespace Neon
{
    void AudioSystem::postUpdate()
    {
        ECS::Registry& registry = Engine::getSceneManager().getCurrentScene().getRegistry();

        auto& audioSources = registry.view<AudioSource, Transform>();

        AudioManager& audioManager = Engine::getAudioManager();

        for (auto [entity, audioSource, transform] : audioSources)
        {
            const bool isPlaying = sounds.contains(audioSource.clip.getID());
            if(audioSource.isPlaying && !isPlaying)
            {
                Sound sound = audioManager.createSound(audioSource.clip.get());
                sound.play();
                sounds.emplace(audioSource.clip.getID(), sound);
            }
            if(audioSource.isPlaying && isPlaying)
            {
                Sound& sound = sounds.at(audioSource.clip.getID());
                sound.setLoop(audioSource.loop);
                sound.setVolume(audioSource.volume);
                sound.setPitch(audioSource.pitch);
                sound.setPosition(transform.getPosition());
            }
            if(!audioSource.isPlaying && isPlaying)
            {
                Sound sound = audioManager.createSound(audioSource.clip.get());
                sound.stop();
                sounds.erase(audioSource.clip.getID());
            }
        }
    }
}
