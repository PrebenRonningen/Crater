#pragma once
#include "CraterEngine.h"
#include "HealthComponent.h"

class HealthDisplayComponent final : public CraterEngine::Component
{
public:
	HealthDisplayComponent(const CraterEngine::GameObject* parent, HealthComponent* healthComponent);
	virtual ~HealthDisplayComponent() override{};

#pragma region deleted
	HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
	HealthDisplayComponent(HealthDisplayComponent&& other) noexcept = delete;
	HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
	HealthDisplayComponent& operator=(HealthDisplayComponent&& other) noexcept = delete;
#pragma endregion

	virtual void Update(const float dt) override;
	virtual bool Initialize() override{ return true; };

private:
	HealthComponent* m_HealthComponent;
	int m_PreviousHealth = -1;
};