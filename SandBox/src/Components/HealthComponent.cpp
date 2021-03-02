#include "CraterPCH.h"
#include "CraterEngine.h"
#include "HealthComponent.h"


HealthComponent::HealthComponent(const CraterEngine::GameObject* parent)
	: Component(parent)
{
}

bool HealthComponent::Initialize()
{
	return true;
}

int HealthComponent::GetRemainingLives() const
{
	return (int)m_Health;
}

void HealthComponent::LoseHealth(std::uint8_t healthLost)
{
	if ( m_Health <= 0 ) return;

	if ( healthLost >= m_Health )
	{
		m_Health = 0;
		Dead();
		return;
	}
	m_Health -= healthLost;
	m_pParent->Notify(*m_pParent, CraterEngine::EventType::LostHealt);
}

void HealthComponent::Dead()
{
	m_pParent->Notify(*m_pParent, CraterEngine::EventType::Died);
}
	
