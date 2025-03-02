#include "GraphCacheComponent.h"
#include <string>
#include <stdexcept>
#include <chrono>
#include <deque>
#include <algorithm>
#include <numeric>
#include <implot.h>
#include <iostream>


GraphCacheComponent::GraphCacheComponent(dae::GameObject& parent) : Component(parent)
{
}

void GraphCacheComponent::Update()
{
    KeepSamplePositive();
}

void GraphCacheComponent::Render()
{
    int stepSizes[11] = { 1,2,4,8,16,32,64,128,256,512,1024 };

    // Exercise 2 Window -------------------------------------------
    ImGui::Begin("Exercise 2");

    ImGui::InputInt("# of samples", m_SampleAmountEx2, 1);

  
    if (ImGui::Button("Trash the Cache"))
    {   
        RunSampleEx2();
    }
    
    if (m_DisplayGraphEx2)
    {
        if (ImPlot::BeginPlot("Int", ImVec2(300, 200)))
        {
            ImPlot::SetupAxes("stepSize", "microseconds", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisScale(ImAxis_X1,ImPlotScale_Log10);

            ImPlot::SetNextLineStyle(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
            ImPlot::PlotLine("Duration in micro seconds", stepSizes, m_Ex2Durations.data(), 11);


            ImPlot::EndPlot();
        }
    }

    ImGui::End();
    // Exercise 2 Window End -------------------------------------------



    // Exercise 3 Window -------------------------------------------
    ImGui::SetNextWindowPos(ImVec2(300, 50), ImGuiCond_FirstUseEver); //makes sure i wont cover exercise 2 with 3

    ImGui::Begin("Exercise 3");

    ImGui::InputInt("# of samples", m_SampleAmountEx3, 1);

    if (ImGui::Button("Trash the Cache with GameObject3D"))
    {
        RunSampleEx3();
    }

    if (m_DisplayGraphEx3)
    {
        if (ImPlot::BeginPlot("GameObject3D", ImVec2(300, 200)))
        {
            ImPlot::SetupAxes("stepSize", "microseconds", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Log10);

            ImPlot::SetNextLineStyle(ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
            ImPlot::PlotLine("Duration in micro seconds", stepSizes, m_Ex3Durations.data(), 11);


            ImPlot::EndPlot();
        }
    }

    if (ImGui::Button("Trash the Cache with GameObject3DAlt"))
    {
        RunSampleEx3Alt();
    }

    if (m_DisplayGraphEx3Alt)
    {
        if (ImPlot::BeginPlot("GameObject3DAlt", ImVec2(300, 200)))
        {
            ImPlot::SetupAxes("stepSize", "microseconds", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Log10);

            ImPlot::SetNextLineStyle(ImVec4(0.0f, 1.0f, 0.7f, 1.0f));
            ImPlot::PlotLine("Duration in micro seconds", stepSizes, m_Ex3DurationsAlt.data(), 11);


            ImPlot::EndPlot();
        }
    }

    if (m_DisplayGraphEx3Alt && m_DisplayGraphEx3)
    {
        if (ImPlot::BeginPlot("Combined", ImVec2(300, 200)))
        {
            ImPlot::SetupAxes("stepSize", "microseconds", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Log10);

            ImPlot::SetNextLineStyle(ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
            ImPlot::PlotLine("Duration in micro seconds", stepSizes, m_Ex3Durations.data(), 11);

            ImPlot::SetNextLineStyle(ImVec4(0.0f, 1.0f, 0.7f, 1.0f));
            ImPlot::PlotLine("Duration in micro seconds", stepSizes, m_Ex3DurationsAlt.data(), 11);


            ImPlot::EndPlot();
        }
    }

    ImGui::End();
}

void GraphCacheComponent::RunSampleEx2()
{
    m_DisplayGraphEx2 = false;

    m_Ex2Durations.clear();

    int stepSize{ 0 };

    std::vector<int> arr (50000000,2);

    std::deque<long long> stepArr{ *m_SampleAmountEx2 };

    for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
    {
        for (int idx = 0; idx < *m_SampleAmountEx2; idx++)
        {
            auto before = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < arr.size(); i += stepSize)
            {
                arr[i] *= 2;
            }
            auto after = std::chrono::high_resolution_clock::now();

            stepArr.emplace_back(std::chrono::duration_cast<std::chrono::microseconds>(after - before).count());
        }
        if (stepArr.size() > 4)
        {
            std::sort(stepArr.begin(), stepArr.end());
            stepArr.pop_back();
            stepArr.pop_front();
        }

        m_Ex2Durations.emplace_back(static_cast<int>(std::accumulate(stepArr.begin(), stepArr.end(), 0LL) / stepArr.size()));
        stepArr.clear();
    }

    m_DisplayGraphEx2 = true;
}

void GraphCacheComponent::RunSampleEx3()
{
    m_DisplayGraphEx3 = false;

    m_Ex3Durations.clear();

    int stepSize{ 0 };

    std::deque<long long> stepArr{ *m_SampleAmountEx3 };
    
    std::vector<GameObject3D> arr{ 50000000 };

    for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
    {
        for (int idx = 0; idx < *m_SampleAmountEx3; idx++)
        {
            auto before = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < arr.size(); i += stepSize)
            {
                arr[i].ID *= 2;
            }
            auto after = std::chrono::high_resolution_clock::now();

            stepArr.emplace_back(std::chrono::duration_cast<std::chrono::microseconds>(after - before).count());
        }
        if (stepArr.size() > 4)
        {
            std::sort(stepArr.begin(), stepArr.end());
            stepArr.pop_back();
            stepArr.pop_front();
        }

        m_Ex3Durations.emplace_back(static_cast<int>(std::accumulate(stepArr.begin(), stepArr.end(), 0LL) / stepArr.size()));
        stepArr.clear();
    }

    m_DisplayGraphEx3 = true;
}

void GraphCacheComponent::RunSampleEx3Alt()
{
    m_DisplayGraphEx3Alt = false;

    m_Ex3DurationsAlt.clear();

    int stepSize{ 0 };

    std::deque<long long> stepArr{ *m_SampleAmountEx3 };

    std::vector<GameObject3DAlt> arr{ 50000000 };

    for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
    {
        for (int idx = 0; idx < *m_SampleAmountEx3; idx++)
        {
            auto before = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < arr.size(); i += stepSize)
            {
                arr[i].ID *= 2;
            }
            auto after = std::chrono::high_resolution_clock::now();

            stepArr.emplace_back(std::chrono::duration_cast<std::chrono::microseconds>(after - before).count());
        }
        if (stepArr.size() > 4)
        {
            std::sort(stepArr.begin(), stepArr.end());
            stepArr.pop_back();
            stepArr.pop_front();
        }

        m_Ex3DurationsAlt.emplace_back(static_cast<int>(std::accumulate(stepArr.begin(), stepArr.end(), 0LL) / stepArr.size()));
        stepArr.clear();
    }

    m_DisplayGraphEx3Alt = true;

}

void GraphCacheComponent::KeepSamplePositive()
{
    if (*m_SampleAmountEx2 < 1) *m_SampleAmountEx2 = 1;

    if (*m_SampleAmountEx3 < 1) *m_SampleAmountEx3 = 1;
    
}

