#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "steam_api.h"

#include "MsPacmanCode.h"
#include <filesystem>
#include "SDLAudioService.h"
#include "SteamAchievements.h"

namespace fs = std::filesystem;

void load()
{
	MsPacmanCode msPacmanCode {};
	msPacmanCode.LoadGameCode();
}

int main(int, char*[])
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	if (SteamAPI_Init())
	{
		g_SteamAchievements = std::make_unique<CSteamAchievements>(g_Achievements, 4);
	}

	dae::Minigin engine(data_location);
	engine.Run(load);

	SteamAPI_Shutdown();
	return 0;
}
