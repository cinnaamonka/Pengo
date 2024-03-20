#pragma once

namespace GameEngine
{
	class IObserver
	{

	public:
		virtual ~IObserver() {};
		virtual void Notify(const int message_from_subject) = 0;
	};
};



