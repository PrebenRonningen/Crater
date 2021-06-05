#include "SandBoxPCH.h"
#include "Crater/Managers/ResourceManager.h"
#include "QbertLevelOneScene.h"
#include "Components/LevelComponent.h"
#include "Components/QbertComponent.h"

using namespace CraterEngine;

QbertLevelOneScene::~QbertLevelOneScene()
{
	m_pPyramid = nullptr;
}

QbertLevelOneScene::QbertLevelOneScene(const std::string& name)
	: Scene(name)
	, m_pPyramid{nullptr}
	, m_qSprite{nullptr}
{
}

void QbertLevelOneScene::Update(const float dt)
{
	for ( auto pO : m_Objects )
	{
		pO->Update(dt);
	}
	time += dt;
	if ( time > neededTime )
	{
		time = 0;
		int col = 0;
		int row = 0;
		m_qSprite->GetRowAndCol(row, col);
		if(col == 0 )
			m_qSprite->SetTextureSource(row, 1);
		else
			m_qSprite->SetTextureSource(row, 0);
	}

}

void QbertLevelOneScene::Render() const
{
	for ( auto pO : m_RenderObjects )
	{
		pO->Render();
	}
}

void QbertLevelOneScene::Initialize()
{
	using namespace CraterEngine;
	{
		//Background
		ResourceManager::GetInstance().Init("../Crater/Data/");
		CraterEngine::GameObject* go = new CraterEngine::GameObject;
		go->AddComponent<TransformComponent>();
		go->AddComponent<SpriteComponent>("background.jpg");

		RegisterComponentToRender(go->GetComponent<SpriteComponent>());
		AddGameObject(go);
	}
	ResourceManager::GetInstance().Init("../SandBox/Resources/Images/");
	{
		m_pPyramid = new GameObject();
		
		m_pPyramid->AddComponent<TransformComponent>(glm::vec3{ 112, 352, 0 }, glm::vec3{0,0,0}, glm::vec3{2,2,2});
		m_pPyramid->AddComponent<SpriteComponent>("Tile/Level2Cube.png", 3);
		m_pPyramid->AddComponent<LevelComponent>(7);

		RegisterComponentToRender(m_pPyramid->GetComponent<LevelComponent>());
		AddGameObject(m_pPyramid);
	}

	{
		GameObject* qBert = new GameObject();
		qBert->AddComponent<TransformComponent>(m_pPyramid->GetComponent<LevelComponent>()->GetSpawnPos(), glm::vec3{ 0,0,0 }, glm::vec3{ 2,2,2 });
		qBert->AddComponent<SpriteComponent>("Qbert/Qbert.png", 1, 8);
		qBert->AddComponent<QbertComponent>();
		qSprite = qBert->GetComponent<SpriteComponent>();
		RegisterComponentToRender(qBert->GetComponent<SpriteComponent>());
		AddGameObject(qBert);
	}
	//pos is +208x = 3*64 + 16
	//pos is -304y = 6*48 + 16

	for ( auto o : m_Objects )
	{
		o->Initialize();
	}
}

