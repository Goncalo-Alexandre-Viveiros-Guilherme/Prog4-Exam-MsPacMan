#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <string>
#include "Audio.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_set>

namespace std::filesystem
{
	class path;
}

class SDLAudioImpl;

class SDLAudio final : public Audio {
public:
    SDLAudio(const std::filesystem::path& data);
    ~SDLAudio() override;

    void AddSound(std::string soundName, int soundChannel, const char* filePathForSound) override;
    void AddMusic(const std::string& musicName, const char* filePathForMusic) override;

    void PlaySound(std::string soundName, int volume = 100, int loops = 0) override;
    void PlayMusic(const std::string& musicName, int volume = 100, int loops = 0) override;

    void PauseSound(std::string soundName) override;
    void PauseMusic() override;
    void PauseAllSounds() override;

    void StopSound(std::string soundName) override;
    void StopAllSounds() override;


    void SetAllAudioVolume(int volume) override;
    void SetChannelVolume(int channel, int volume) override;
    void SetSoundVolume(std::string soundName, int volume) override;
    void SetMusicVolume(int volume) override;

    void Run();

private:
    std::unique_ptr<SDLAudioImpl> m_pImpl;
    std::queue<std::function<void()>> m_EventQueue;
    std::mutex m_QueueMutex;
    std::condition_variable m_Condition;
    std::thread m_WorkerThread;
    std::atomic<bool> m_Running{ true };
};
