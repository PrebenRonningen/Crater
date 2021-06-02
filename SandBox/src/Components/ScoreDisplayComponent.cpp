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
		const auto& renderable = m_pParent->GetComponent<CraterEngine::RenderableComponent>();
		std::stringstream displayText;
		displayText << renderable->GetText();
		displayText << currentScore;
		renderable->SetText(displayText.str());

		m_PreviousScore = currentScore;
	}
}