#pragma once
namespace GameEngine
{
	class General
	{
	public:

		inline static constexpr char TITLE[] = "Engine";

		inline static constexpr int WINDOW_WIDTH = 640;
		inline static constexpr int WINDOW_HEIGHT = 480;

		inline static constexpr char CONTENT_PATH[] = "Data/";

		inline static constexpr double FIXED_TIME_STEP = 1.0 / 60.0;

		inline static constexpr int TARGET_FPS = 60;
	};
}


