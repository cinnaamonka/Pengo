#include "../pch.h"

std::vector<float> RunArrayComputationBenchmark(int arraySize, int numIterations);
template<typename T>
std::vector<float> RunObject3DComputation(int arraySize, int numIterations, T* arr)
{
	const int maxStep = 1024;
	std::vector<float> finalAverageTimings{};

	for (int i = 0; i < arraySize; ++i)
	{
		arr[i].ID = 1;
	}

	int step = 1;

	while (step <= maxStep)
	{
		std::vector<float> timings{};

		for (int iteration = 0; iteration < numIterations; ++iteration)
		{
			auto start_time = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < arraySize; i += step)
			{
				arr[i].ID *= 2;
			}

			auto end_time = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end_time - start_time);

			timings.push_back(duration.count());
		}

		std::sort(timings.begin(), timings.end());

		if (timings.size() > 2)
		{
			timings.erase(timings.begin());
			timings.erase(timings.end() - 1);
		}

		float totalTiming = 0.0f;

		for (float timing : timings)
		{
			totalTiming += timing;
		}

		float averageTiming = totalTiming / (numIterations - numIterations / 5);

		finalAverageTimings.push_back(averageTiming);

		if (step != maxStep)
		{
			step *= 2;
		}
		else {
			break;
		}
	}

	return finalAverageTimings;
}

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

class GameObject3D
{
public:
	Transform transform;
	int ID;
};
class GameObject3DAlt
{
public:
	Transform* transform;
	int ID;
};

static int inputValueFirstInput = 0;
static int inputValueSecondField = 0;

static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
static uint32_t selection_start = 0, selection_length = 0;
static char inputTextBuffer[256] = "";
static char inputSecondTextBuffer[256] = "";


void DrawPlot(std::vector<float> benchmarkResults)
{
	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.ys = benchmarkResults.data();
	conf.values.count = static_cast<int>(benchmarkResults.size());
	conf.values.colors = colors;
	conf.scale.min = -1;
	conf.scale.max = 20;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_x.size = 60;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = 0.5f;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(200, 100);

	ImGui::Plot("plot1", conf);
}
void DrawDoublePlot(std::vector<float> benchmarkResults, std::vector<float> benchmarkResults2)
{
    const float* y_data[] = { benchmarkResults.data(), benchmarkResults2.data()};

	ImGui::PlotConfig conf;
	conf.values.count = static_cast<int>(benchmarkResults.size());
	conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 2;
	conf.values.colors = colors;
	conf.scale.min = -1;
	conf.scale.max = 20;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_x.size = 60;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = 0.5f;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(200, 100);
	ImGui::Plot("plot1", conf);
}

void ImGui::ShowMyWindow(bool* p_open)
{
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");

	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 100, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL;

	static int resultStep;
	static std::vector<float> benchmarkResults;


	if (!ImGui::Begin("Exercise 1", p_open, window_flags))
	{
		ImGui::End();
		return;
	}

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
			const int arraySize = 1 << 26;

			inputValueFirstInput = std::atoi(inputTextBuffer);
			sprintf_s(inputTextBuffer, "%d", inputValueFirstInput);

			benchmarkResults = RunArrayComputationBenchmark(arraySize, inputValueFirstInput);

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
		DrawPlot(benchmarkResults);
	}
	ImGui::PopItemWidth();
	ImGui::End();
}
void ImGui::ShowSecondWindow(bool* p_open)
{
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");

	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 100, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           p_open = NULL;

	static int resultStep;
	static std::vector<float> benchmarkResults;
	static std::vector<float> benchmarkResults2;

	const int arraySize = 1 << 26;

	if (!ImGui::Begin("Exercise 2", p_open, window_flags))
	{
		ImGui::End();
		return;
	}

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

			benchmarkResults = RunObject3DComputation(arraySize, inputValueSecondField, arr);

			calculateBenchmarkSecondExercise = false;

			delete[] arr;
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

			benchmarkResults2 = RunObject3DComputation(arraySize, inputValueSecondField, arr);

			calculateBenchmarkThirdExercise = false;

			delete[] arr;
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
		DrawPlot(benchmarkResults);
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
		DrawPlot(benchmarkResults2);
	}

	// combined 
	if (benchmarkResults2.size() > 0 && benchmarkResults.size() > 0)
	{
		DrawDoublePlot(benchmarkResults, benchmarkResults2);
	}
	ImGui::PopItemWidth();
	ImGui::End();
}
std::vector<float> RunArrayComputationBenchmark(int arraySize, int numIterations)
{
	int* arr = new int[arraySize];
	const int maxStep = 1024;
	std::vector<float> finalAverageTimings{};

	for (int i = 0; i < arraySize; ++i)
	{
		arr[i] = 1;
	}

	int step = 1;

	while (step <= maxStep)
	{
		std::vector<float> timings{};

		for (int iteration = 0; iteration < numIterations; ++iteration)
		{
			auto start_time = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < arraySize; i += step)
			{
				arr[i] *= 2;
			}

			auto end_time = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end_time - start_time);

			timings.push_back(duration.count());
		}

		std::sort(timings.begin(), timings.end());

		if (timings.size() > 2)
		{
			timings.erase(timings.begin());
			timings.erase(timings.end() - 1);
		}


		float totalTiming = 0.0f;

		for (float timing : timings)
		{
			totalTiming += timing;
		}

		float averageTiming = totalTiming / (numIterations - numIterations / 5);

		finalAverageTimings.push_back(averageTiming);

		if (step != maxStep)
		{
			step *= 2;
		}
		else {
			break;
		}
	}


	delete[] arr;
	return finalAverageTimings;
}


