#pragma once

static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
static uint32_t selection_start = 0, selection_length = 0;

void DrawBasicWindow(bool* p_open, const char* name)
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


	if (!ImGui::Begin(name, p_open, window_flags))
	{
		ImGui::End();
		return;
	}
}

template <typename T, typename Operation>
std::vector<float> RunComputationBenchmark(int arraySize, int numIterations, T* arr, Operation operation)
{
	const int maxStep = 1024;
	std::vector<float> finalAverageTimings{};

	for (int i = 0; i < arraySize; ++i)
	{
		operation(arr[i]);
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
				operation(arr[i]);
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

void DrawPlot(const float* data[], int size, int amount = 1)
{
	ImGui::PlotConfig conf;
	if (amount > 1)
	{
		const float* y_data[] =
		{
		  data[0],
		  data[1]
		};

		conf.values.ys_list = y_data;
		conf.values.ys_count = 2;
	}
	else
	{
		conf.values.ys = data[0];
	}

	conf.values.count = size;

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

