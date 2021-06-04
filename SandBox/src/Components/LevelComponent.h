#pragma once
#include <CraterEngine.h>

class LevelComponent final : public CraterEngine::Component
{
public:
	LevelComponent(const CraterEngine::GameObject* parent);
	virtual ~LevelComponent() = default;
#pragma region deleted
	LevelComponent(const LevelComponent& other) = delete;
	LevelComponent(LevelComponent&& other) = delete;
	LevelComponent& operator=(const LevelComponent& other) = delete;
	LevelComponent& operator=(LevelComponent&& other) = delete;
#pragma endregion


	inline float randF(float min, float max)
	{
		const float random = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX );
		const float diff = max - min;
		const float r = random * diff;
		return min + r;
	}

	virtual void Update(const float dt) override;
	virtual bool Initialize() override{m_IsInitialized = true; return true;};
	virtual void Render() const override;
private:

	float m_AccumulatedTime;
	float m_NeededTime;
};

