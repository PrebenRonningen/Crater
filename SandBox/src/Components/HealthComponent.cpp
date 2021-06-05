#include "SandBoxPCH.h"
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
	SetEvent(HealthEvent::LostHealth);
	m_pParent->Notify( );
}

void HealthComponent::Dead()
{
	SetEvent(HealthEvent::Died);
	m_pParent->Notify();
}
	
