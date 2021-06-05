#pragma once
#include "CraterEngine.h"

class HealthObserver final : public CraterEngine::Observer
{
public:
	HealthObserver() = default;
	virtual ~HealthObserver() override
	{
	};

	#pragma region deleted
	HealthObserver(const HealthObserver& other) = delete;
	HealthObserver(HealthObserver&& other) noexcept = delete;
	HealthObserver& operator=(const HealthObserver& other) = delete;
	HealthObserver& operator=(HealthObserver&& other) noexcept = delete;
	#pragma endregion

	virtual void OnNotify(const CraterEngine::GameObject* pObject) override;
	private:
};
