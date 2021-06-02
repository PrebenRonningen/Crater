#include "SandBoxPCH.h"
#include "CraterEngine.h"
#include "PlayerComponent.h"

std::uint8_t PlayerComponent::m_TotalPlayerCount = 0;
PlayerComponent::PlayerComponent(const CraterEngine::GameObject* parent)
	: Component{parent}
{
	m_PlayerID = m_TotalPlayerCount;
	++m_TotalPlayerCount;
}

PlayerComponent::~PlayerComponent()
{
	--m_TotalPlayerCount;
}
