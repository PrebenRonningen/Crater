#pragma once
#include <CraterEngine.h>
class MovementComponent final : public CraterEngine::Component
{
public:
	MovementComponent(const CraterEngine::GameObject* parent);
	virtual ~MovementComponent() = default;

#pragma region deleted
	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) = delete;
#pragma endregion

	virtual void Update(const float dt) override
	{
		dt;
	};
	virtual bool Initialize() override;
	virtual void Render() const override
	{
	};

private:
	bool m_CanMove;
};

