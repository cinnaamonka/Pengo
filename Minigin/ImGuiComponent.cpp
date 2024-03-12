#include "ImGuiComponent.h"
#include "BaseComponent.h"

#include <functional>

GameEngine::ImGuiComponent::ImGuiComponent(GameObject* gameObject) :BaseComponent(gameObject)
{
	m_ChartUpdateInfoPtr->buttonText = "Trash the cache";
	m_ChartUpdateInfoPtr->color = ImColor(0, 255, 0);

	m_GameObjectChartUpdateInfoPtr->buttonText = "Trash the cache with GameObject3D";
	m_GameObjectChartUpdateInfoPtr->color = ImColor(0, 0, 255);

	m_AltGameObjectChartUpdateInfoPtr->buttonText = "Trash the cache with GameObject3DAlt";
	m_AltGameObjectChartUpdateInfoPtr->color = ImColor(255, 0, 0);
}

void GameEngine::ImGuiComponent::Render()
{
	RenderExercise1();

	RenderExercise2();
}

void GameEngine::ImGuiComponent::RenderExercise1()
{
	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_None);
	static int samplesNumber = 0;
	ImGui::InputInt("# samples:", &samplesNumber);

	ManagePlotUpdateStages<int>(m_ChartUpdateInfoPtr.get(), samplesNumber);
	ImGui::Plot("Plot", *m_ChartUpdateInfoPtr->plotConfig);
	ImGui::End();
}

void GameEngine::ImGuiComponent::RenderExercise2()
{
	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_None);

	static int numberOfSamples{ 100 };
	ImGui::InputInt("# samples:", &numberOfSamples);

	ManagePlotUpdateStages<GameObject3D>(m_GameObjectChartUpdateInfoPtr.get(), numberOfSamples);
	ImGui::Plot("GameObj plot", *m_GameObjectChartUpdateInfoPtr->plotConfig);

	ManagePlotUpdateStages<GameObject3DAlt>(m_AltGameObjectChartUpdateInfoPtr.get(), numberOfSamples);
	ImGui::Plot("AltGameObj plot", *m_AltGameObjectChartUpdateInfoPtr->plotConfig);

	if (!m_AltGameObjectChartUpdateInfoPtr->averageTime.empty() && !m_GameObjectChartUpdateInfoPtr->averageTime.empty())
	{
		RenderCombinedConf();
		ImGui::Plot("Combined plot", *m_CombinedChartPtr);
	}

	ImGui::End();
}
void GameEngine::ImGuiComponent::RenderCombinedConf()
{
	ImGui::Text("Combined:");

	static const float* y_data[] = { m_AltGameObjectChartUpdateInfoPtr->averageTime.data(), m_GameObjectChartUpdateInfoPtr->averageTime.data() };

	*m_CombinedChartPtr = *m_GameObjectChartUpdateInfoPtr->plotConfig;
	m_CombinedChartPtr->values.color = 0;
	m_CombinedChartPtr->values.colors = colors;
	m_CombinedChartPtr->values.ys = nullptr;
	m_CombinedChartPtr->values.ys_list = y_data;
	m_CombinedChartPtr->values.ys_count = 2;
	m_CombinedChartPtr->scale.max = std::max(*std::max_element(m_GameObjectChartUpdateInfoPtr->averageTime.begin(), m_GameObjectChartUpdateInfoPtr->averageTime.end()),
		*std::max_element(m_AltGameObjectChartUpdateInfoPtr->averageTime.begin(), m_AltGameObjectChartUpdateInfoPtr->averageTime.end())) + 1;
}




