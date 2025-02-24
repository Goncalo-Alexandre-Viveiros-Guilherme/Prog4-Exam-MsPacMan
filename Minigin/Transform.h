#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		Transform();

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& pos);
		void SetWorldPosition(float x, float y, float z);
		void SetWorldPosition(const glm::vec3& pos);
		

	private:
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
	};
}
