#pragma once
#include <string>
#include <functional>
#include <filesystem>

namespace dae
{
	class Minigin final
	{
		
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();
		void DeleteObjects(std::string sceneName);
		void Run(const std::function<void()>& load);
		void Fixed_update(float fixedTimeStep);
		static void Update();
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		float fixed_time_step{ 0.02f };
		std::chrono::milliseconds ms_per_frame{16};
		bool m_quit{};
	};
}