#pragma once
#include "BaseComponent.h"


namespace GameEngine
{
	class ImGuiComponent : public BaseComponent
	{
	public:
		ImGuiComponent(GameObject* gameObject);
		~ImGuiComponent() {};

		virtual void Render() const override;
		void RenderExercise1() const;
		void RenderExercise2()const;


	};
}

