#pragma once
#include "CraterEngine.h"
#include "ScoreComponent.h"

class ScoreDisplayComponent final : public CraterEngine::Component
{
public:
	ScoreDisplayComponent(const CraterEngine::GameObject* parent, ScoreComponent* scoreComp);
	virtual ~ScoreDisplayComponent() override{};

#pragma region deleted
	ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent(ScoreDisplayComponent&& other) noexcept = delete;
	ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) noexcept = delete;
#pragma endregion

	virtual void Update(const float dt) override;
	//virtual void Render() const override;
	virtual bool Initialize() override { return true; };

private:
	ScoreComponent* m_pScoreComponent;
	int m_PreviousScore = -1;
};