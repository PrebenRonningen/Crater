#pragma once
#include <CraterEngine.h>
class LevelComponent;
class MovementComponent final : public CraterEngine::Component
{
public:
	MovementComponent(const CraterEngine::GameObject* parent, LevelComponent* levelComponent);
	virtual ~MovementComponent() = default;

#pragma region deleted
	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) = delete;
#pragma endregion

	virtual void Update(const float dt) override;
	virtual bool Initialize() override;
	virtual void Render() const override
	{
	};

	void MoveUpLeft();
	void MoveUpRight();
	void MoveDownLeft();
	void MoveDownRight();
	void Move(glm::ivec2& target);

	glm::vec3 GetCurrentPosition() const { return glm::vec3(m_CurrentPosition.x, m_CurrentPosition.y, 0); }

	enum class MoveEvent
	{
		None,
		QbertJumpUp,
		QbertJumpDown,
		QbertLanded,
	} m_CurrentEvent = MoveEvent::None;

	void SetEvent(const MoveEvent& moveEvent)
	{
		m_HasEvent = true;
		m_CurrentEvent = moveEvent;
	}
	const MoveEvent& GetEvent() const
	{
		return m_CurrentEvent;
	}
	virtual void EventHandeled() override
	{
		m_CurrentEvent = MoveEvent::None;
		m_HasEvent = false;
	};

private:
	enum MoveState
	{
		Idle,
		InTransit,
		Landed,
		OffMap

	}m_MoveState = MoveState::Idle;


	bool m_CanMove;
	bool m_IsPlayer;
	bool m_IsTargetOnTile;
	float m_Speed;
	LevelComponent* m_LevelComponent;
	CraterEngine::TransformComponent* m_TransformComp;
	glm::ivec2 m_StartingPosition;
	glm::vec2 m_CurrentPosition;
	glm::ivec2 m_TargetPosition;
	glm::ivec2 m_Distance;
	glm::vec3 m_TransformTarget;
};

