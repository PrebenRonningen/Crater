#include "CraterPCH.h"
#include "CraterEngine.h"
#include "ScoreComponent.h"

ScoreComponent::ScoreComponent(const CraterEngine::GameObject* parent)
	: Component(parent)
{
}

bool ScoreComponent::Initialize()
{
	return true;
}

void ScoreComponent::Update(const float)
{
}
