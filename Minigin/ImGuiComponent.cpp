#include "ImGuiComponent.h"
#include "BaseComponent.h"
#include "ImGuiFunctions.h"

#include <functional>

int framesCountFirstExercise = 0;
int framesCountSecondExercise = 0;
int framesCountThirdExercise = 0;

bool calculateBenchmarkFirstExercise = false;
bool calculateBenchmarkSecondExercise = false;
bool calculateBenchmarkThirdExercise = false;
bool shouldWaitFirstExercise = false;
bool shouldWaitSecondExercise = false;
bool shouldWaitThirdExercise = false;

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
};
struct MultiplyID
{
	void operator()(BasicGameObject& element) const
	{
		element.ID *= 2;
	}
};

static int inputValueFirstInput = 0;
static int inputValueSecondField = 0;


static char inputTextBuffer[256] = "";
static char inputSecondTextBuffer[256] = "";


GameEngine::ImGuiComponent::ImGuiComponent(GameObject* gameObject) :BaseComponent(gameObject)
{

}

void GameEngine::ImGuiComponent::Render() const
{
	RenderExercise1();

	RenderExercise2();
}

void GameEngine::ImGuiComponent::RenderExercise1()const
{
	DrawBasicWindow("Exercise 1");

	static int resultStep;
	static std::vector<float> benchmarkResults;

	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	ImGui::InputText("#samples", inputTextBuffer, IM_ARRAYSIZE(inputTextBuffer), ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::SameLine();
	if (ImGui::Button("+"))
	{
		inputValueFirstInput++;
		sprintf_s(inputTextBuffer, "%d", inputValueFirstInput);
	}

	ImGui::SameLine();
	if (ImGui::Button("-"))
	{
		inputValueFirstInput--;
		sprintf_s(inputTextBuffer, "%d", inputValueFirstInput);
	}

	ImGui::NewLine();

	if (shouldWaitFirstExercise)
	{
		ImGui::Text("Wait a second, i am calculating...");
		calculateBenchmarkFirstExercise = true;
		framesCountFirstExercise++;
	}

	if (framesCountFirstExercise == 2)
	{
		if (calculateBenchmarkFirstExercise)
		{
			inputValueFirstInput = std::atoi(inputTextBuffer);
			sprintf_s(inputTextBuffer, "%d", inputValueFirstInput);

			const int arraySize = 1 << 26;
			int* arr = new int[arraySize];
			auto intOperation = [](int& element) { element *= 2; };

			benchmarkResults = RunComputationBenchmark(arraySize, inputValueFirstInput, arr, intOperation);

			calculateBenchmarkFirstExercise = false;
		}

		framesCountFirstExercise = 0;
		shouldWaitFirstExercise = false;
	}

	if (!shouldWaitFirstExercise)
	{
		if (ImGui::Button("Run Benchmark") && strlen(inputTextBuffer) > 0)
		{
			shouldWaitFirstExercise = true;
		}
	}

	if (strlen(inputTextBuffer) > 0)
	{
		inputValueFirstInput = std::atoi(inputTextBuffer);
		sprintf_s(inputTextBuffer, "%d", inputValueFirstInput);
	}

	if (benchmarkResults.size() > 0)
	{
		const float* data[] = { benchmarkResults.data() };
		DrawPlot(data, static_cast<int>(benchmarkResults.size()));
	}
	ImGui::PopItemWidth();
	ImGui::End();
}

void GameEngine::ImGuiComponent::RenderExercise2()const
{

	DrawBasicWindow("Exercise 2");

	static int resultStep;
	static std::vector<float> benchmarkResults;
	static std::vector<float> benchmarkResults2;
	std::function<void(BasicGameObject&)> multiplyFunction = MultiplyID();

	const int arraySize = 1 << 23;

	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	ImGui::InputText("#samples", inputSecondTextBuffer, IM_ARRAYSIZE(inputSecondTextBuffer), ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::SameLine();
	if (ImGui::Button("+"))
	{
		inputValueSecondField++;
		sprintf_s(inputSecondTextBuffer, "%d", inputValueSecondField);
	}

	ImGui::SameLine();
	if (ImGui::Button("-"))
	{
		inputValueSecondField--;
		sprintf_s(inputSecondTextBuffer, "%d", inputValueSecondField);
	}

	ImGui::NewLine();

	if (shouldWaitSecondExercise)
	{
		ImGui::Text("Wait a second, i am calculating...");
		calculateBenchmarkSecondExercise = true;
		framesCountSecondExercise++;
	}
	if (shouldWaitThirdExercise)
	{
		ImGui::Text("Wait a second, i am calculating...");
		calculateBenchmarkThirdExercise = true;
		framesCountThirdExercise++;
	}


	if (framesCountSecondExercise == 2)
	{
		if (calculateBenchmarkSecondExercise)
		{

			inputValueSecondField = std::atoi(inputSecondTextBuffer);
			sprintf_s(inputSecondTextBuffer, "%d", inputValueSecondField);

			GameObject3D* arr = new GameObject3D[arraySize];

			benchmarkResults = RunComputationBenchmark(arraySize, inputValueSecondField, arr, multiplyFunction);

			calculateBenchmarkSecondExercise = false;
		}

		framesCountSecondExercise = 0;
		shouldWaitSecondExercise = false;
	}
	if (framesCountThirdExercise == 2)
	{
		if (calculateBenchmarkThirdExercise)
		{
			inputValueSecondField = std::atoi(inputSecondTextBuffer);
			sprintf_s(inputSecondTextBuffer, "%d", inputValueSecondField);

			GameObject3DAlt* arr = new GameObject3DAlt[arraySize];

			benchmarkResults2 = RunComputationBenchmark(arraySize, inputValueSecondField, arr, multiplyFunction);

			calculateBenchmarkThirdExercise = false;
		}

		framesCountThirdExercise = 0;
		shouldWaitThirdExercise = false;
	}

	if (!shouldWaitSecondExercise)
	{
		if (ImGui::Button("Trash the cache with GameObject3D") && strlen(inputSecondTextBuffer) > 0)
		{
			shouldWaitSecondExercise = true;
		}
	}

	if (strlen(inputSecondTextBuffer) > 0)
	{
		inputValueSecondField = std::atoi(inputSecondTextBuffer);
		sprintf_s(inputSecondTextBuffer, "%d", inputValueSecondField);
	}

	if (benchmarkResults.size() > 0)
	{
		const float* data[] = { benchmarkResults.data() };
		DrawPlot(data, static_cast<int>(benchmarkResults.size()));
	}
	if (!shouldWaitThirdExercise)
	{
		if (ImGui::Button("Trash the cache with GameObject3DAlt") && strlen(inputSecondTextBuffer) > 0)
		{
			shouldWaitThirdExercise = true;
		}
	}

	if (benchmarkResults2.size() > 0)
	{
		const float* data[] = { benchmarkResults2.data() };
		DrawPlot(data, static_cast<int>(benchmarkResults2.size()));
	}

	// combined 
	if (benchmarkResults2.size() > 0 && benchmarkResults.size() > 0)
	{
		ImGui::Text("Combined:");
		const float* data[] = { benchmarkResults.data() ,benchmarkResults2.data() };

		DrawPlot(data, static_cast<int>(benchmarkResults.size()), 2);
	}
	ImGui::PopItemWidth();
	ImGui::End();
}




