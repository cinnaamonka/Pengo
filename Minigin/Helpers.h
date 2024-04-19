#ifndef HELPERS_H
#define HELPERS_H

#include "json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

#include "BaseComponent.h"

namespace GameEngine
{
	void GetVerticesFromJsonFile(std::string fileName, std::vector<std::vector<glm::vec3>>& m_Vertices, 
		std::vector<std::vector<glm::vec3>>& m_VerticesSecondType, std::vector<std::vector<glm::vec3>>& m_BorderVertices);

	struct HitInfo
	{
		float lambda;
		glm::vec2 intersectPoint;
		glm::vec2 normal;
	};
	struct Rect
	{
		int left;
		int bottom;
		int width;
		int height;
	};

	bool IsOverlapping(const Rect& r1, const Rect& r2);


	bool IsPointOnLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b);


	bool IntersectLineSegments(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2, float& outLambda1,
		float& outLambda2, float epsilon = 1e-6);



	bool Raycast(const glm::vec3* vertices, const size_t nrVertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);

	bool Raycast(const std::vector<glm::vec3>& vertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);

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

	class Blackboard final
	{
	public:
		Blackboard() = default;
		~Blackboard()
		{
			for (auto el : m_BlackboardData)
				delete el.second;
			m_BlackboardData.clear();

		}

		Blackboard(const Blackboard& other) = delete;
		Blackboard& operator=(const Blackboard& other) = delete;
		Blackboard(Blackboard&& other) = delete;
		Blackboard& operator=(Blackboard&& other) = delete;

		template<typename T> bool AddData(const std::string& name, T data)
		{
			auto it = m_BlackboardData.find(name);
			if (it == m_BlackboardData.end())
			{
				m_BlackboardData[name] = new BlackboardField<T>(data);
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
				BlackboardField<T>* p = dynamic_cast<BlackboardField<T>*>(m_BlackboardData[name]);
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
			BlackboardField<T>* p = dynamic_cast<BlackboardField<T>*>(m_BlackboardData[name]);
			if (p != nullptr)
			{
				data = p->GetData();
				return true;
			}
			printf("WARNING: Data '%s' of type '%s' not found in Blackboard \n", name.c_str(), typeid(T).name());
			return false;
		}

	private:
		std::unordered_map<std::string, IBlackBoardField*> m_BlackboardData;
	};

	class FSMState
	{
	public:
		FSMState() = default;
		virtual ~FSMState() = default;

		virtual void OnEnter(Blackboard* pBlackboard) = 0;
		virtual void OnExit(Blackboard* pBlackboard) = 0;
		virtual void Update(Blackboard* pBlackboard) = 0;

	};

	class FSMCondition
	{
	public:
		FSMCondition() = default;
		virtual ~FSMCondition() = default;
		virtual bool Evaluate(Blackboard* pBlackboard) const = 0;
	};
}

#endif // HELPERS_H