#include "SandBoxPCH.h"
#include "QbertComponent.h"
#include "LevelComponent.h"

QbertComponent::QbertComponent(const CraterEngine::GameObject* parent, LevelComponent* levelComponent)
	:Component(parent)
	, m_LevelComponent{ levelComponent }
	, m_Time{0}
	, m_NeededTime{1}
{
}

void QbertComponent::Update(const float dt)
{
	m_Time += dt;
	if ( m_Time > m_NeededTime )
	{
		m_Time = 0;
		int col = 0;
		int row = 0;
		m_pSprite->GetRowAndCol(row, col);
		if ( col % 2 )
			m_pSprite->SetTextureSource(row, --col);
		else
			m_pSprite->SetTextureSource(row, ++col);
	}
}

bool QbertComponent::Initialize()
{
	m_pSprite = m_pParent->GetComponent<CraterEngine::SpriteComponent>();
	return true;
}
