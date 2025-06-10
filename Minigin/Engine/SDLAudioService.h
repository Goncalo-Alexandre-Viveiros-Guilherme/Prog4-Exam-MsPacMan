#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <string>
#include "AudioService.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>

namespace std::filesystem
{
	class path;
}

class SDLAudioImpl;

class SDLAudio final : public Audio
{
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


class LoggingSoundSystem final : public Audio
{
    std::unique_ptr<Audio> _real_ss;
public:
    LoggingSoundSystem(std::unique_ptr<Audio>&& ss) : _real_ss(std::move(ss)) {}

    virtual ~LoggingSoundSystem() = default;


    void AddSound(std::string soundName, int soundChannel, const char* filePathForSound) override
    {
        _real_ss->AddSound(soundName, soundChannel, filePathForSound);
        std::cout << "Added sound: " << soundName << " from " << filePathForSound << std::endl;
    }

    void AddMusic(const std::string& musicName, const char* filePathForMusic) override
    {
        _real_ss->AddMusic(musicName, filePathForMusic);
        std::cout << "Added music: " << musicName << " from " << filePathForMusic << std::endl;
    }

    void PlaySound(std::string soundName, int volume = 100, int loops = 0) override
    {
        _real_ss->PlaySound(soundName, volume, loops);
        std::cout << "Playing sound: " << soundName << " at volume " << volume << " and loops " << loops << std::endl;
    }

    void PlayMusic(const std::string& musicName, int volume = 100, int loops = 0) override
    {
        _real_ss->PlayMusic(musicName, volume, loops);
        std::cout << "Playing music: " << musicName << " at volume " << volume << " and loops " << loops << std::endl;
    }

    void PauseSound(std::string soundName) override
    {
        _real_ss->PauseSound(soundName);
        std::cout << "Paused sound: " << soundName << std::endl;
    }

    void PauseMusic() override
    {
        _real_ss->PauseMusic();
        std::cout << "Paused music" << std::endl;
    }

    void PauseAllSounds() override
    {
        _real_ss->PauseAllSounds();
        std::cout << "Paused all sounds" << std::endl;
    }

    void StopSound(std::string soundName) override
    {
        _real_ss->StopSound(soundName);
        std::cout << "Stopped sound: " << soundName << std::endl;
    }

    void StopAllSounds() override
    {
        _real_ss->StopAllSounds();
        std::cout << "Stopped all sounds" << std::endl;
    }

    void SetAllAudioVolume(int volume) override
    {
        _real_ss->SetAllAudioVolume(volume);
        std::cout << "Set all audio volume to: " << volume << std::endl;
    }

    void SetChannelVolume(int channel, int volume) override
    {
        _real_ss->SetChannelVolume(channel, volume);
        std::cout << "Set volume for channel " << channel << " to: " << volume << std::endl;
    }

    void SetSoundVolume(std::string soundName, int volume) override
    {
        _real_ss->SetSoundVolume(soundName, volume);
        std::cout << "Set volume for sound " << soundName << " to: " << volume << std::endl;
    }

    void SetMusicVolume(int volume) override
    {
        _real_ss->SetMusicVolume(volume);
        std::cout << "Set music volume to: " << volume << std::endl;
    }
};