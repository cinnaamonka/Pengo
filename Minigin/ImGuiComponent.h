#pragma once
#include "BaseComponent.h"

#include <set>
#include <string>
#include <chrono>

#include <numeric>

#include <../imgui-1.89.5/imgui_plot.h>
#define IMGUI_DEFINE_MATH_OPERATORS

#include <../imgui-1.89.5/imgui.h>
#include <../imgui-1.89.5/backends/imgui_impl_sdl2.h>
#include <../imgui-1.89.5/backends/imgui_impl_opengl3.h>
#include <SDL_stdinc.h>

static uint32_t selection_start = 0, selection_length = 0;
static ImU32 colors[2] = { ImColor(255, 0, 0), ImColor(0, 0, 255) };

struct Transform
{
	float matrix[16] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};
class BasicGameObject
{
public:

	int ID;
};
class GameObject3D : public BasicGameObject
{
public:

	Transform transform;
};
class GameObject3DAlt :public BasicGameObject
{
public:
	Transform* transform;

	~GameObject3DAlt() { delete transform; };
};

enum class ChartStage
{
	notUpdated,
	hideButton,
	showText,
	updateChart
};

struct ChartInfo
{
	ChartStage chartStage = ChartStage::notUpdated;
	std::string buttonText = { "" };
	std::unique_ptr<ImGui::PlotConfig> plotConfig = std::make_unique< ImGui::PlotConfig>();
	std::vector<float> averageTime = {};
	ImU32 color = {};
};

namespace GameEngine
{
	class ImGuiComponent final : public BaseComponent
	{
	public:
		explicit ImGuiComponent(GameObject* gameObject);
		~ImGuiComponent() {};

		virtual void Render() override;

	private:
		std::unique_ptr<ChartInfo> m_ChartUpdateInfoPtr = std::make_unique<ChartInfo>();
		std::unique_ptr<ChartInfo> m_GameObjectChartUpdateInfoPtr = std::make_unique<ChartInfo>();
		std::unique_ptr<ChartInfo> m_AltGameObjectChartUpdateInfoPtr = std::make_unique<ChartInfo>();
		std::unique_ptr<ImGui::PlotConfig> m_CombinedChartPtr = std::make_unique< ImGui::PlotConfig>();
	private:
		void RenderExercise1();
		void RenderExercise2();

		template<typename T>
		void CalculateTimeAverage(int numberOfSamples, std::vector<float>& averageTimes)
		{
			constexpr int arrSize{ (std::is_same<T, int>::value) ? 67108864 : 10000000 };
			T* arr = new T[arrSize]{};
			std::vector<std::set<long>> timesRecorded(11);

			for (int j = 0; j < numberOfSamples; j++)
			{
				int index = -1;
				for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
				{
					auto start_time = std::chrono::high_resolution_clock::now();

					for (int i = 0; i < arrSize; i += stepsize)
					{
						if constexpr (std::is_same<T, int>::value) 
						{
							arr[i] *= 2;
						}
						else if constexpr (std::is_same<T, GameObject3D>::value || std::is_same<T, GameObject3DAlt>::value) 
						{
							arr[i].ID *= 2;
						}

					}
					auto end_time = std::chrono::high_resolution_clock::now();

					const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
					timesRecorded[++index].insert(static_cast<long>(total));
				}

			}

			delete[] arr;
			averageTimes.clear();

			for (auto& durations : timesRecorded)
			{
				auto minmax = std::minmax_element(durations.begin(), durations.end());
				auto timeAverage = std::accumulate(durations.begin(), durations.end(), 0LL) - (*minmax.first) - (*minmax.second);
				auto averageDuration = static_cast<float>(timeAverage) / (durations.size() - 2);
				averageTimes.push_back(averageDuration / 100.f);
			}
		}

		template<typename T>
		void UpdatePlot(ChartInfo* chartUpdateInfo, int numberOfSamples)
		{
			static constexpr size_t buf_size = 11;
			static float x_data[buf_size] = { 1,2,4,8,16,32,64,128,256,512,1024 };

			CalculateTimeAverage<T>(numberOfSamples, chartUpdateInfo->averageTime);
			chartUpdateInfo->plotConfig->values.xs = x_data;
			chartUpdateInfo->plotConfig->values.ys = chartUpdateInfo->averageTime.data();
			chartUpdateInfo->plotConfig->values.count = buf_size;
			chartUpdateInfo->plotConfig->values.color = chartUpdateInfo->color;
			chartUpdateInfo->plotConfig->scale.min = 0;
			chartUpdateInfo->plotConfig->scale.max = *std::max_element(chartUpdateInfo->averageTime.begin(), chartUpdateInfo->averageTime.end()) + 1;
			chartUpdateInfo->plotConfig->tooltip.show = true;
			chartUpdateInfo->plotConfig->grid_x.show = false;
			chartUpdateInfo->plotConfig->grid_y.show = true;
			chartUpdateInfo->plotConfig->selection.show = true;
			chartUpdateInfo->plotConfig->selection.start = &selection_start;
			chartUpdateInfo->plotConfig->selection.length = &selection_length;
			chartUpdateInfo->plotConfig->frame_size = ImVec2(250, 150);
			chartUpdateInfo->plotConfig->line_thickness = 2.f;
		}

		template<typename T>
		void ManagePlotUpdateStages(ChartInfo* plotUpdateInfo, int nrOfSamples)
		{
			switch (plotUpdateInfo->chartStage)
			{
			case ChartStage::notUpdated:

				if (ImGui::Button(plotUpdateInfo->buttonText.c_str()))
				{
					plotUpdateInfo->chartStage = ChartStage::hideButton;
				}

				break;
			case ChartStage::hideButton:

				plotUpdateInfo->chartStage = ChartStage::showText;

				break;
			case ChartStage::showText:

				ImGui::Text("Wait, i am calculating..");

				plotUpdateInfo->chartStage = ChartStage::updateChart;

				break;

			case ChartStage::updateChart:

				UpdatePlot<T>(plotUpdateInfo, nrOfSamples);

				plotUpdateInfo->chartStage = ChartStage::notUpdated;

				break;
			}
		}

		void RenderCombinedConf();
	};
}

