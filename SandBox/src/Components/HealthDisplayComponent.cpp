#include "CraterPCH.h"
#include "CraterEngine.h"
#include "HealthDisplayComponent.h"
#include <sstream>

HealthDisplayComponent::HealthDisplayComponent(const CraterEngine::GameObject* parent, HealthComponent* healthComponent)
	: Component(parent)
	, m_HealthComponent{ healthComponent }
{
;
}

void HealthDisplayComponent::Update(const float)
{
	if ( m_HealthComponent->GetRemainingLives() != m_PreviousHealth )
	{
		int currentHealth = m_HealthComponent->GetRemainingLives();
		const auto& renderable = m_pParent->GetComponent<CraterEngine::RenderableComponent>();
		std::stringstream displayText;
		displayText << renderable->GetText();
		displayText << currentHealth;
		renderable->SetText(displayText.str());

		m_PreviousHealth = currentHealth;
	}
}
