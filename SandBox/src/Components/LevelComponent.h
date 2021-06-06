#pragma once
#include <CraterEngine.h>
#include "QbertComponent.h"
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
		bool IsOccupiedByPlayer = false;
	};

public:
	enum class LevelEvent
	{
		None,
		QbertLanded,
		QbertJump

	} m_CurrentEvent = LevelEvent::None;
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


	virtual void EventHandeled() override
	{
		m_CurrentEvent = LevelEvent::None;
		m_HasEvent = false;
	};

	const glm::ivec3& GetSpawnPos() const  {return m_SpawnPos;};
	void SetEvent(const LevelEvent& levelEvent)
	{
		m_HasEvent = true;
		m_CurrentEvent = levelEvent;
	}
	const LevelEvent& GetEvent() const
	{
		return m_CurrentEvent;
	}

	bool Move(const bool isPlayer, bool& isTargetOnTile, const glm::ivec2& target);

	void RegisterPlayer(QbertComponent* qbert);

	void FlipCube(const glm::vec3& cubeAtPostions);
	void PlayerLeftCube(const glm::vec3& PlayerAtPostions);
	glm::ivec2 GetCubeStartPosition() const;
private:
	inline float randF(float min, float max)
	{
		const float random = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX );
		const float diff = max - min;
		const float r = random * diff;
		return min + r;
	}
	void CalculateSpawnPos();
	void SetupLevel();
	int m_Height;
	int m_NumCubes;
	glm::ivec3 m_SpawnPos;
	std::vector<Cube> m_Cubes;
	std::vector<float> m_AccumulatedTime;
	std::vector<float> m_NeededTime;
	std::vector<QbertComponent*> m_Players;
};

