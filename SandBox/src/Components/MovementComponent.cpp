#include "SandBoxPCH.h"
#include "MovementComponent.h"
#include "LevelComponent.h"

MovementComponent::MovementComponent(const CraterEngine::GameObject* parent, LevelComponent* levelComponent)
	:Component(parent)
	, m_CanMove{true}
	, m_LevelComponent{ levelComponent }
	, m_TargetPosition{0, 0}
	, m_StartingPosition{}
	, m_CurrentPosition{}
	, m_Distance{16, 24}
	, m_IsPlayer{false}
	, m_Speed{3.f}
	, m_IsTargetOnTile{true}
	, m_TransformTarget{} 
{
	
}

void MovementComponent::Update(const float dt)
{
	dt;
	if ( m_MoveState == MoveState::Idle )
	{
		//m_MoveState = MoveState::OffMap;
	}
	else
	{
		glm::vec2 transit{};
		glm::vec3 pos{};
		glm::vec2 dir{};
		switch ( m_MoveState )
		{
			case MovementComponent::Idle:
				break;
			case MovementComponent::InTransit:
					transit = m_TargetPosition - m_StartingPosition;
					m_CurrentPosition += transit * dt * m_Speed;
					dir = glm::vec2(m_TargetPosition) - m_CurrentPosition;

					m_TransformComp->MovePosition(transit * dt * m_Speed);
					if ( glm::dot(dir, transit) <= 0)
					{
						m_MoveState = MoveState::Landed;
					}
					m_pParent->GetComponent<CraterEngine::SpriteComponent>()->UpdateDestination();
				break;
			case MovementComponent::Landed:
				m_CurrentPosition = m_StartingPosition = m_TargetPosition;
				m_TransformComp->SetPosition(m_TransformTarget);
				if ( m_IsPlayer )
				{
					m_MoveState = m_IsTargetOnTile ? MoveState::Idle : MoveState::OffMap;
					if ( m_MoveState == MoveState::Idle )
					{
						m_CanMove = true;
						SetEvent(MoveEvent::QbertLanded);
						m_LevelComponent->SetEvent(LevelComponent::LevelEvent::QbertLanded);
						m_pParent->Notify();
					}
				}
				break;
			case MovementComponent::OffMap:
				//fall and die
					std::cout << "FALLING\n";
					m_TransformComp->MovePosition(0, m_Distance.y * dt * m_Speed, 0);

				break;
			default:
				break;
		}
	}
}

bool MovementComponent::Initialize()
{
	m_TransformComp = m_pParent->GetComponent<CraterEngine::TransformComponent>();
	auto startPosition = m_LevelComponent->GetCubeStartPosition();
	auto scale = m_TransformComp->GetScale();
	m_StartingPosition = m_CurrentPosition = startPosition;
	m_Distance.x =int( m_Distance.x * scale.x);
	m_Distance.y =int( m_Distance.y * scale.y);
	m_IsPlayer = m_pParent->HasComponent<QbertComponent>();
	return true;
}

void MovementComponent::MoveUpLeft()
{
	if ( m_CanMove )
	{
	//	m_IsTargetOnTile = false;
		glm::ivec2 target = -m_Distance; 
		// this is entirely to ensure that the transform aftermovement ends up in the correct position independent of time when "Landed"
		m_TransformTarget = m_TransformComp->GetPosition() + glm::vec3(target.x, target.y, 0);
		target += m_StartingPosition;
		Move(target);
	}
	if ( m_IsPlayer )
	{
		CraterEngine::SpriteComponent* pSprite = m_pParent->GetComponent<CraterEngine::SpriteComponent>();
		glm::ivec2 rowCol{};
		pSprite->GetRowAndCol(rowCol.x, rowCol.y);
		if ( rowCol.y % 2 )
			pSprite->SetTextureSource(rowCol.x, 7);
		else
			pSprite->SetTextureSource(rowCol.x, 6);

	}
}


void MovementComponent::MoveUpRight()
{
	if ( m_CanMove )
	{
		//	m_IsTargetOnTile = false;
		glm::ivec2 target = {m_Distance.x, -m_Distance.y};
		m_TransformTarget = m_TransformComp->GetPosition() + glm::vec3(target.x, target.y, 0);
		target += m_StartingPosition;
		Move(target);
	}	if ( m_IsPlayer )
	{
		CraterEngine::SpriteComponent* pSprite = m_pParent->GetComponent<CraterEngine::SpriteComponent>();

		glm::ivec2 rowCol{};
		pSprite->GetRowAndCol(rowCol.x, rowCol.y );
		if( rowCol.y % 2 )
			pSprite->SetTextureSource(rowCol.x, 5);
		else
			pSprite->SetTextureSource(rowCol.x, 4);
	}
}

void MovementComponent::MoveDownLeft()
{
	if ( m_CanMove )
	{
		//	m_IsTargetOnTile = false;
		glm::ivec2 target = { -m_Distance.x, m_Distance.y };
		m_TransformTarget = m_TransformComp->GetPosition() + glm::vec3(target.x, target.y, 0);
		target += m_StartingPosition;
		Move(target);
	}
	if ( m_IsPlayer )
	{
		CraterEngine::SpriteComponent* pSprite = m_pParent->GetComponent<CraterEngine::SpriteComponent>();
	
		glm::ivec2 rowCol{};
		pSprite->GetRowAndCol(rowCol.x, rowCol.y);
		if ( rowCol.y % 2 )
			pSprite->SetTextureSource(rowCol.x, 3);
		else
			pSprite->SetTextureSource(rowCol.x, 2);

	}
}

void MovementComponent::MoveDownRight()
{
	if ( m_CanMove )
	{
		//	m_IsTargetOnTile = false;
		glm::ivec2 target = m_Distance;
		m_TransformTarget = m_TransformComp->GetPosition() + glm::vec3(target.x, target.y, 0);
		target += m_StartingPosition;
		Move(target);
	}
	if ( m_IsPlayer )
	{
		CraterEngine::SpriteComponent* pSprite = m_pParent->GetComponent<CraterEngine::SpriteComponent>();
		glm::ivec2 rowCol{};
		pSprite->GetRowAndCol(rowCol.x, rowCol.y);
		if ( rowCol.y % 2 )
			pSprite->SetTextureSource(rowCol.x, 1);
		else
			pSprite->SetTextureSource(rowCol.x, 0);

	}
}
void MovementComponent::Move(glm::ivec2& target)
{
	if ( m_LevelComponent->Move(m_IsPlayer, m_IsTargetOnTile, target) )
	{
		m_TargetPosition = target;
		m_MoveState = MoveState::InTransit;
		m_CanMove = false;
		if ( m_IsPlayer )
		{
			SetEvent(MoveEvent::QbertJumpUp);
			m_LevelComponent->SetEvent(LevelComponent::LevelEvent::QbertJump);
			m_pParent->Notify();
		}
	}
}
