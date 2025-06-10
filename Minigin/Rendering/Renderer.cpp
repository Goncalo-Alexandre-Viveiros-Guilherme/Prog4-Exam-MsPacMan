#include <stdexcept>
#include <cstring>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <implot.h>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	ImPlot::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y,const float scaleX,const float scaleY) const
{

	int texW, texH;
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &texW, &texH);
	const float scaledW = texW * scaleX;
	const float scaledH = texH * scaleY;

	SDL_Rect dst{};
	dst.x = static_cast<int>(x );
	dst.y = static_cast<int>(y );
	dst.w = static_cast<int>(scaledW);
	dst.h = static_cast<int>(scaledH);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, 
	const float width, const float height, const float scaleX, const float scaleY) const
{

	const float scaledW = width * scaleX;
	const float scaledH = height * scaleY;

	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(scaledW);
	dst.h = static_cast<int>(scaledH);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& src,
	glm::vec2 dstPos, const float scaleX, const float scaleY) const
{

	int texW, texH;
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &texW, &texH);
	const float scaledW = texW * scaleX;
	const float scaledH = texH * scaleY;

	SDL_Rect dst{};
	dst.x = static_cast<int>(dstPos.x);
	dst.y = static_cast<int>(dstPos.y);
	dst.w = static_cast<int>(scaledW);
	dst.h = static_cast<int>(scaledH);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect src, SDL_Rect dst, const float scaleX, const float scaleY) const
{

	const float scaledW = dst.w * scaleX;
	const float scaledH = dst.h * scaleY;

	dst.x = static_cast<int>(dst.x);
	dst.y = static_cast<int>(dst.y);
	dst.w = static_cast<int>(scaledW);
	dst.h = static_cast<int>(scaledH);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void dae::Renderer::RenderDebugRect(const float width, const float height, const float posX, const float posY) const
{
	SDL_Rect rect{};
	rect.x = posX;
	rect.y = posY;
	rect.w = width;
	rect.h = height;

	SDL_SetRenderDrawColor(GetSDLRenderer(), 0, 50, 255, 255);
	SDL_RenderDrawRect(GetSDLRenderer(), &rect);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
