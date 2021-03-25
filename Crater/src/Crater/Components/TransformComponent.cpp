#include "CraterPCH.h"
#include "TransformComponent.h"
#include "Crater/GameObject.h"

namespace CraterEngine
{
	TransformComponent::TransformComponent(const GameObject* parent, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: Component(parent)
		, m_Position{position}
		, m_Rotation{rotation}
		, m_Scale{scale}
	{
	}
	
	TransformComponent::~TransformComponent()
	{
	}

	bool TransformComponent::Initialize()
	{
		return true;
	}
	void TransformComponent::Update(const float)
	{
	}

	void TransformComponent::SetPosition(const float x, const float y, const float z)
	{
		SetPosition(glm::vec3(x, y, z));
	}
	void TransformComponent::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}
	void TransformComponent::SetRotation(float x, float y, float z)
	{
		SetRotation(glm::vec3(x, y, z));
	}
	void TransformComponent::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
	}
	void TransformComponent::SetScale(float x, float y, float z)
	{
		SetScale(glm::vec3(x, y, z));
	}
	void TransformComponent::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
	}
}
