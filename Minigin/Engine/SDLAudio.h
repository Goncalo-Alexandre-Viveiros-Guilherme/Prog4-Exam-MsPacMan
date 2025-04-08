#pragma once

#include <memory>
#include <string>
#include "Audio.h"  // Your abstract base class

// Forward declaration of implementation class
class SDLAudioImpl;

class SDLAudio final : public Audio {
public:
    SDLAudio();
    ~SDLAudio() override;

    // Override Audio interface methods
    void AddSound(std::string soundName, int soundChannel, const char* filePathForSound) override;
    void PlaySound(std::string soundName, int loops = 0) override;
    void PauseSound(std::string soundName) override;
    void PauseAllSounds() override;
    void StopSound(std::string soundName) override;
    void StopAllSounds() override;

private:
    std::unique_ptr<SDLAudioImpl> pImpl;  // Pointer-to-implementation
};
