#pragma once
#include <cstdint>

class CraterEngine::GameObject;
class HealthComponent final : public CraterEngine::Component
{
public:
	enum class HealthEvent
	{
		LostHealth,
		Died
	} m_CurrentEvent;


	HealthComponent(const CraterEngine::GameObject* parent);
	virtual ~HealthComponent() override{};

#pragma region deleted
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) noexcept = delete;
#pragma endregion

	virtual void Update(const float ) override{};
	//virtual void Render() const override;
	virtual bool Initialize() override;

	int GetRemainingLives() const;

	void LoseHealth(std::uint8_t  healthLost);
	void Dead();

	void SetEvent(const HealthEvent& healthEvent)
	{
		m_HasEvent = true; m_CurrentEvent = healthEvent;
	}
	const HealthEvent& GetEvent() const
	{
		return m_CurrentEvent;
	}

private:
	std::uint8_t m_MaxHealth = 3;
	std::uint8_t m_Health = m_MaxHealth;
	bool m_IsAlive = true;
};