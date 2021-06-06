#include "SandBoxPCH.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(const CraterEngine::GameObject* parent)
	:Component(parent)
	, m_CanMove{true}
{
}

bool MovementComponent::Initialize()
{
	return false;
}
