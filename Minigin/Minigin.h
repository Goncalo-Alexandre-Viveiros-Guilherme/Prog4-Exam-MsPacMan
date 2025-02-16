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
		static void DeleteObjects(std::string sceneName);
		void Run(const std::function<void()>& load);
		void Fixed_update();
		static void Update();
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		bool m_quit{};
		double m_Lag{};
	};
}