#include "CraterPCH.h"
#include "GameObject.h"
#include "Crater/Managers/ResourceManager.h"
#include "Renderer.h"

namespace CraterEngine
{
	GameObject::~GameObject() = default;

	void GameObject::Update()
	{
	}

	void GameObject::Render() const
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}

	void GameObject::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void GameObject::SetPosition(float x, float y)
	{
		m_Transform.SetPosition(x, y, 0.0f);
	}
}