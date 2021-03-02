#pragma once
#include <cstdint>

class CraterEngine::GameObject;
class HealthComponent : public CraterEngine::Component
{
public:
	HealthComponent(const CraterEngine::GameObject* parent);
	virtual ~HealthComponent() override{};

#pragma region deleted
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) noexcept = delete;
#pragma endregion

	virtual void Update(const float dt) override{dt;};
	//virtual void Render() const override;
	virtual bool Initialize() override;

	int GetRemainingLives() const;

	void LoseHealth(std::uint8_t  healthLost);
	void Dead();

private:
	std::uint8_t m_MaxHealth = 3;
	std::uint8_t m_Health = m_MaxHealth;
	bool m_IsAlive = true;
};