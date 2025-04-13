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

class SDLAudioImpl;

class SDLAudio final : public Audio {
public:
    SDLAudio();
    ~SDLAudio() override;

    void AddSound(std::string soundName, int soundChannel, const char* filePathForSound) override;
    void AddMusic(const char* filePathForMusic) override;
    void PlaySound(std::string soundName, int loops = 0) override;
    void PlayMusic(int loops) override;
    void PauseSound(std::string soundName) override;
    void PauseMusic() override;
    void PauseAllSounds() override;
    void StopSound(std::string soundName) override;
    void StopAllSounds() override;

    void Run();

private:
    std::unique_ptr<SDLAudioImpl> pImpl;
    std::queue<std::function<void()>> m_EventQueue;
    std::mutex m_QueueMutex;
    std::condition_variable m_Condition;
    std::thread m_WorkerThread;
    std::atomic<bool> m_Running{ true };
};
