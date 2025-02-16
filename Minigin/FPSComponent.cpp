#include "FPSComponent.h"

#include "EngineTime.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <iomanip>
#include <sstream>

FPSComponent::FPSComponent(const dae::GameObject* parent): Component(parent), m_Fps(0)
{
}


void FPSComponent::Update()
{
	if (m_Timer >= m_Threshold)
	{
        m_Fps = 1 / Time::GetInstance().GetDeltaTime();

        if (m_Parent->HasComponent<TextComponent>())
        {
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(2) << m_Fps;
            const std::string fpsString = stream.str();

            m_Parent->GetComponent<TextComponent>().SetText(fpsString);
        }

        m_Timer = 0;
	}

	else
	{
        m_Timer += Time::GetInstance().GetDeltaTime();
	}

}

float FPSComponent::GetFps() const
{
    return m_Fps;
}


