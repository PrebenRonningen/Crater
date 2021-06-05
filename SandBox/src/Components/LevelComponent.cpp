#include "SandBoxPCH.h"
#include "LevelComponent.h"
#include <ctime>
#include <random>

LevelComponent::LevelComponent(const CraterEngine::GameObject* parent, const int pyramidHeight)
	:Component(parent)
	,m_Height{pyramidHeight}
{
	for(int i{}; i < m_Height; ++i )
		for(int j{}; j < m_Height-i; ++j )
			m_NumCubes++;

	for ( int i{}; i < m_NumCubes; ++i )
	{
		if( randF(0.0f, 100.f) > 50 )
			m_NeededTime.push_back(randF(0.125f, 0.25f));
		else
			m_NeededTime.push_back(randF(2.5f, 5.0f));
	}

	m_AccumulatedTime.resize(m_NumCubes, 0);

	CalculateSpawnPos();
}

void LevelComponent::Update(const float dt)
{
	for ( int i{}; i < m_NumCubes; ++i )
	{
		m_AccumulatedTime[i] += dt;
		if ( m_AccumulatedTime[i] >= m_NeededTime[i] )
		{
			m_AccumulatedTime[i] -= m_NeededTime[i];
			
			auto* k = m_pParent->GetComponent<CraterEngine::SpriteComponent>();
			int col{};
			k->GetRowAndCol(m_Cubes[i].stage, col);
			m_Cubes[i].stage++;
			//k->SetTextureSource(++row, col);
		}
	}
}

bool LevelComponent::Initialize()
{
	SetupLevel();
	m_IsInitialized = true;
	return true;
}

void LevelComponent::Render() const
{
	auto* k = m_pParent->GetComponent<CraterEngine::SpriteComponent>();

	for ( Cube c :  m_Cubes)
	{
		k->SetDestination(c.pos.x, c.pos.y);
		k->SetTextureSource(c.stage, 0);
		k->Render();
	}
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
