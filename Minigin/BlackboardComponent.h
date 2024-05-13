#pragma once
#include "BaseComponent.h"
#include "Helpers.h"
#include <string>

namespace GameEngine
{
	class BlackboardComponent;

	class IBlackBoardField
	{
	public:
		IBlackBoardField() = default;
		virtual ~IBlackBoardField() = default;
	};

	template<typename T>
	class BlackboardField : public IBlackBoardField
	{
	public:
		explicit BlackboardField(T data) : m_Data(data)
		{}
		T GetData() { return m_Data; };
		void SetData(T data) { m_Data = data; }

	private:
		T m_Data;
	};

	class FSMState
	{
	public:
		FSMState() = default;
		virtual ~FSMState() = default;

		virtual void OnEnter(AnimationComponent* pBlackboard) = 0;
		virtual void OnExit(AnimationComponent* pBlackboard) = 0;
		virtual void Update(AnimationComponent* pBlackboard) = 0;
	};

	class FSMCondition
	{
	public:
		FSMCondition() = default;
		virtual ~FSMCondition() = default;
		virtual bool Evaluate(AnimationComponent* pBlackboard) const = 0;
	};

	/*class BlackboardComponent : public GameEngine::BaseComponent
	{
	public:
		BlackboardComponent(GameEngine::GameObject* pGameObject);
		~BlackboardComponent()
		{
			for (auto el : m_BlackboardData)
				delete el.second;
			m_BlackboardData.clear();

		}

		BlackboardComponent(const BlackboardComponent& other) = delete;
		BlackboardComponent& operator=(const BlackboardComponent& other) = delete;
		BlackboardComponent(BlackboardComponent&& other) = delete;
		BlackboardComponent& operator=(BlackboardComponent&& other) = delete;

		template<typename T> bool AddData(const std::string& name, T data)
		{
			auto it = m_BlackboardData.find(name);
			if (it == m_BlackboardData.end())
			{
				m_BlackboardData[name] = new GameEngine::BlackboardField<T>(data);
				return true;
			}
			printf("WARNING: Data '%s' of type '%s' already in Blackboard \n", name.c_str(), typeid(T).name());
			return false;
		}

		template<typename T> bool ChangeData(const std::string& name, T data)
		{
			auto it = m_BlackboardData.find(name);
			if (it != m_BlackboardData.end())
			{
				GameEngine::BlackboardField<T>* p = dynamic_cast<GameEngine::BlackboardField<T>*>(m_BlackboardData[name]);
				if (p)
				{
					p->SetData(data);
					return true;
				}
			}
			printf("WARNING: Data '%s' of type '%s' not found in Blackboard \n", name.c_str(), typeid(T).name());
			return false;
		}

		template<typename T> bool GetData(const std::string& name, T& data)
		{
			GameEngine::BlackboardField<T>* p = dynamic_cast<GameEngine::BlackboardField<T>*>(m_BlackboardData[name]);
			if (p != nullptr)
			{
				data = p->GetData();
				return true;
			}
			printf("WARNING: Data '%s' of type '%s' not found in Blackboard \n", name.c_str(), typeid(T).name());
			return false;
		}

		void Destroy(); 

	private:
		std::unordered_map<std::string, GameEngine::IBlackBoardField*> m_BlackboardData; 

	};*/


}



