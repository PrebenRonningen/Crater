#include "SandBoxPCH.h"
#include "LevelComponent.h"
#include <ctime>
#include <random>
#include "ScoreComponent.h"
#include "MovementComponent.h"

LevelComponent::LevelComponent(const CraterEngine::GameObject* parent, const int pyramidHeight)
	:Component(parent)
	,m_Height{pyramidHeight}
{
	for(int i{}; i < m_Height; ++i )
		for(int j{}; j < m_Height-i; ++j )
			m_NumCubes++;
	//
	//for ( int i{}; i < m_NumCubes; ++i )
	//{
	//	if( randF(0.0f, 100.f) > 50 )
	//		m_NeededTime.push_back(randF(0.125f, 0.25f));
	//	else
	//		m_NeededTime.push_back(randF(2.5f, 5.0f));
	//}
	//
	//m_AccumulatedTime.resize(m_NumCubes, 0);

	CalculateSpawnPos();
}

void LevelComponent::Update(const float dt)
{
dt;
//	for ( int i{}; i < m_NumCubes; ++i )
//	{
//		m_AccumulatedTime[i] += dt;
//		if ( m_AccumulatedTime[i] >= m_NeededTime[i] )
//		{
//			m_AccumulatedTime[i] -= m_NeededTime[i];
//			
//			auto* k = m_pParent->GetComponent<CraterEngine::SpriteComponent>();
//			int col{};
//			k->GetRowAndCol(m_Cubes[i].stage, col);
//			m_Cubes[i].stage++;
//			//k->SetTextureSource(++row, col);
//		}
//	}
}

bool LevelComponent::Initialize()
{
	SetupLevel();
	m_IsInitialized = true;
	return true;
}

void LevelComponent::Render() const
{
	CraterEngine::SpriteComponent* pSprite = m_pParent->GetComponent<CraterEngine::SpriteComponent>();

	for ( Cube c :  m_Cubes)
	{
		pSprite->SetDestination(c.pos.x, c.pos.y);
		pSprite->SetTextureSource(c.stage, 0);
		pSprite->Render();
	}
}

bool LevelComponent::Move(const bool isPlayer, bool& isTargetOnTile, const glm::ivec2& target )
{
	if ( isPlayer )
	{
		auto it = std::find_if(m_Cubes.begin(), m_Cubes.end(), [target](Cube c){return c.pos == glm::ivec3(target.x, target.y, 0);});
		if ( it != m_Cubes.end() )
		{
			
			isTargetOnTile = true;
			return !it->IsOccupiedByPlayer;
		}
		else
		{
			isTargetOnTile = false;
		}

		return true;
	}

	return false;
}

void LevelComponent::RegisterPlayer(CraterEngine::GameObject* qbert)
{
	m_Players.push_back(qbert);
}

void LevelComponent::FlipCube(const glm::vec3& cubeAtPostions)
{
	
	glm::ivec3 cubePos = cubeAtPostions;
	//glm::ivec2 qBertSpriteSize{ 16, 16 };
	//cubePos.x -= qBertSpriteSize.x;
	//cubePos.y += qBertSpriteSize.y;


	auto cube = std::find_if(m_Cubes.begin(), m_Cubes.end(), [cubePos](Cube c){ return cubePos == c.pos;});
	if ( cube != m_Cubes.end() )
	{
		cube->IsOccupiedByPlayer = true;
		switch ( cube->state )
		{
			case Cube::SwitchState::Permanent:
				if ( cube->stage == 0 )
				{
					cube->stage++;
					for ( auto player : m_Players )
					{
						auto pos = player->GetComponent<MovementComponent>()->GetCurrentPosition();
						if ( cube->pos == glm::ivec3(pos) )
						{
							player->GetComponent<ScoreComponent>()->SetEvent(ScoreComponent::ScoreEvent::ColorChange);
							player->Notify();
							break;
						}
					}
				}
				break;
			case Cube::SwitchState::Reverting:
				if ( cube->stage != 0 )
					cube->stage--;
				break;
			case Cube::SwitchState::MultiStage:
				if ( cube->stage <= 1 )
					cube->stage++;
				//else
				//	cube->stage--;
				break;
			default:
				break;
		}
	}
	if ( LevelCleared() )
	{
		SetEvent(LevelEvent::LeveleCleared);
		m_pParent->Notify();
	}
}

void LevelComponent::PlayerLeftCube(const glm::vec3& PlayerAtPostions)
{
	auto cube = std::find_if(m_Cubes.begin(), m_Cubes.end(), [PlayerAtPostions](Cube c) 
							{
								 return glm::ivec3(PlayerAtPostions) == c.pos;
							 });
	if ( cube != m_Cubes.end() )
	{
		cube->IsOccupiedByPlayer = false;
	}
}

glm::ivec2 LevelComponent::GetCubeStartPosition() const
{
	glm::ivec2 topCubePos = glm::ivec2(m_Cubes.back().pos.x, m_Cubes.back().pos.y);
	return topCubePos;
}

bool LevelComponent::LevelCleared() const
{
	auto cube = std::find_if(m_Cubes.begin(), m_Cubes.end(), [](Cube c)
							 {
								 return c.stage == 0;
							 });
	 if(cube != m_Cubes.end() )
		return false;
	else
		return true;
}

void LevelComponent::CalculateSpawnPos()
{
	auto trans = m_pParent->GetComponent<CraterEngine::TransformComponent>();
	glm::vec3 PyramidWorldPos = trans->GetPosition();
	glm::vec3 scale = trans->GetScale();

	float blocksToTop = m_Height - 1.0f;
	float blocksToMiddle = blocksToTop / 2.0f;

	glm::vec2 qBertSpriteSize{16,16};
	glm::vec2 cubeSize{ Cube::size * scale.x, Cube::size * 0.75f * scale.y };

	qBertSpriteSize.x *= scale.x;
	qBertSpriteSize.y *= scale.y;


	m_SpawnPos = glm::ivec3{ PyramidWorldPos.x + ( blocksToMiddle * cubeSize.x + qBertSpriteSize.x / 2.f ),
							 PyramidWorldPos.y - ( blocksToTop * cubeSize.y + qBertSpriteSize.y / 2.f ),
							 0 };
}

void LevelComponent::SetupLevel()
{
	const auto& scale = m_pParent->GetComponent<CraterEngine::TransformComponent>()->GetScale();
	glm::ivec3 cubePos{};
	for ( int i{}; i < m_Height; ++i )
	{
		Cube cube{};
		for ( int j{}; j < m_Height-i; ++j )
		{
			cube.pos = cubePos;
			m_Cubes.push_back(cube);
			cubePos.x += cube.size* int(scale.x);
		}
		cubePos.x = ((i+1)* cube.size/2) * int(scale.x);
		cubePos.y -= int(cube.size*0.75f)* int(scale.y);
	}
}
