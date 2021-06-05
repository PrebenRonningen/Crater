#pragma once
#include <CraterEngine.h>

class LevelComponent final : public CraterEngine::Component
{
	struct Cube
	{
		glm::ivec3 pos = {0,0,0};
		enum SwitchState
		{
			Permanent = 0,
			MultiStage = 1,
			Reverting = 2
		} state = SwitchState::Permanent;
		int stage = 0;
		
		static const int size = 32;
	};

public:
	LevelComponent(const CraterEngine::GameObject* parent, const int pyramidHeight = 7);
	virtual ~LevelComponent() = default;
#pragma region deleted
	LevelComponent(const LevelComponent& other) = delete;
	LevelComponent(LevelComponent&& other) = delete;
	LevelComponent& operator=(const LevelComponent& other) = delete;
	LevelComponent& operator=(LevelComponent&& other) = delete;
#pragma endregion

	virtual void Update(const float dt) override;
	virtual bool Initialize() override;
	virtual void Render() const override;


	inline float randF(float min, float max)
	{
		const float random = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX );
		const float diff = max - min;
		const float r = random * diff;
		return min + r;
	}

	const glm::ivec3& GetSpawnPos() const  {return m_SpawnPos;};
private:
	void CalculateSpawnPos();
	void SetupLevel();
	int m_Height;
	int m_NumCubes;
	glm::ivec3 m_SpawnPos;
	std::vector<Cube> m_Cubes;
	std::vector<float> m_AccumulatedTime;
	std::vector<float> m_NeededTime;
};

