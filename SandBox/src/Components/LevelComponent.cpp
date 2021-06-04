#include "SandBoxPCH.h"
#include "LevelComponent.h"
#include <ctime>
#include <random>

LevelComponent::LevelComponent(const CraterEngine::GameObject* parent)
	:Component(parent)
{

	m_NeededTime = randF(0.25f, 0.75f);
}

void LevelComponent::Update(const float dt)
{
	m_AccumulatedTime += dt;
	if ( m_AccumulatedTime >= m_NeededTime )
	{
		m_AccumulatedTime -= m_NeededTime;

		auto* k = m_pParent->GetComponent<CraterEngine::SpriteComponent>();
		int row{};
		int col{};
		k->GetRowAndCol(row, col);
		k->SetTextureSource(++row, col);
	}
}

void LevelComponent::Render() const
{
}
