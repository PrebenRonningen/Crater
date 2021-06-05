#include "SandBoxPCH.h"
#include "ScoreDisplayComponent.h"
#include "PlayerComponent.h"
#include <sstream>
ScoreDisplayComponent::ScoreDisplayComponent(const CraterEngine::GameObject* parent, ScoreComponent* scoreComp)
	: Component(parent)
	, m_pScoreComponent{ scoreComp }
{
}

void ScoreDisplayComponent::Update(const float)
{
	if ( m_pScoreComponent->GetScore() != m_PreviousScore )
	{
		int currentScore = m_pScoreComponent->GetScore();
		CraterEngine::TextComponent* pTextComp = m_pParent->GetComponent<CraterEngine::TextComponent>();
		std::stringstream displayText;
		displayText << pTextComp->GetText();
		displayText << currentScore;
		pTextComp->SetText(displayText.str());

		m_PreviousScore = currentScore;
	}
}