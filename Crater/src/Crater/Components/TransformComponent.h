#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "Component.h"

namespace CraterEngine
{
	class GameObject;
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(const GameObject* parent, const glm::vec3& position = glm::vec3{0.0f, 0.0f ,0.0f}, const glm::vec3& rotation = glm::vec3{ 0.0f, 0.0f ,0.0f }, const glm::vec3& scale = glm::vec3{ 1.0f, 1.0f ,1.0f });
		virtual ~TransformComponent() override;

		#pragma region deleted
		TransformComponent(const TransformComponent&) = delete;
		TransformComponent(TransformComponent&&) = delete;
		TransformComponent& operator= (const TransformComponent&) = delete;
		TransformComponent& operator= (const TransformComponent&&) = delete;
		#pragma endregion

		virtual bool Initialize() override;
		virtual void Update(const float dt) override;

		const glm::vec3& GetPosition() const
		{
			return m_Position;
		}
		const glm::vec3& GetRotation() const
		{
			return m_Rotation;
		}
		const glm::vec3& GetScale() const
		{
			return m_Scale;
		}

		void MovePosition(float x, float y, float z)
		{
			m_Position.x += x;
			m_Position.y += y;
			m_Position.z += z;
		}
		void MovePosition(glm::vec3 moveAmount)
		{
			m_Position += moveAmount;
		}
		void MovePosition(glm::vec2 moveAmount)
		{
			MovePosition({moveAmount.x, moveAmount.y, 0});
		}

		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& position);
		void SetRotation(float x, float y, float z);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(float x, float y, float z);
		void SetScale(const glm::vec3& scale);
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}
