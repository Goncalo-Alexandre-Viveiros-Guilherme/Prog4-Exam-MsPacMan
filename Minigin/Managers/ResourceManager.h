#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <map>
#include <unordered_set>

#include "Singleton.h"

class Audio;

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::filesystem::path& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		static std::string GetResourcePath(const std::string& file);
		void LoadAudio(const std::string& soundName, int soundChannel, const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, uint8_t size);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		static std::filesystem::path m_DataPath;

		void UnloadUnusedResources();

		std::map<std::string, std::shared_ptr<Texture2D>> m_LoadedTextures;
		std::map<std::pair<std::string, uint8_t>, std::shared_ptr<Font>> m_LoadedFonts;

	};
}
