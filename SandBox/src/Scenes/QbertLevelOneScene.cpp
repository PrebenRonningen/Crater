#include "SandBoxPCH.h"
#include "Crater/Managers/ResourceManager.h"
#include "QbertLevelOneScene.h"
#include "Components/LevelComponent.h"

using namespace CraterEngine;

QbertLevelOneScene::~QbertLevelOneScene()
{
	m_pPyramid = nullptr;
}

QbertLevelOneScene::QbertLevelOneScene(const std::string& name)
	: Scene(name)
	, m_pPyramid{nullptr}
{
}

void QbertLevelOneScene::Update(const float dt)
{
	for ( auto pO : m_Objects )
	{
		pO->Update(dt);
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
		go->AddComponent<RenderableComponent>();
		go->AddComponent<SpriteComponent>("background.jpg");
		AddGameObject(go);
	}
	ResourceManager::GetInstance().Init("../SandBox/Resources/Images/");
	{
		m_pPyramid = new GameObject();
		m_pPyramid->AddComponent<TransformComponent>(glm::vec3{ 150,400, 0 });
		m_pPyramid->AddComponent<RenderableComponent>();
		m_pPyramid->AddComponent<SpriteComponent>("Tile/Level1Cube.png", 2);
		m_pPyramid->AddComponent<LevelComponent>();

		AddGameObject(m_pPyramid);
	}
	{
		GameObject* pPyramid = new GameObject();
		pPyramid->AddComponent<TransformComponent>(glm::vec3{ 182,400, 0 });
		pPyramid->AddComponent<RenderableComponent>();
		pPyramid->AddComponent<SpriteComponent>("Tile/Level1Cube.png", 2);
		pPyramid->AddComponent<LevelComponent>();

		AddGameObject(pPyramid);
	}
	{
		GameObject* pPyramid = new GameObject();
		pPyramid->AddComponent<TransformComponent>(glm::vec3{ 214,400, 0 });
		pPyramid->AddComponent<RenderableComponent>();
		pPyramid->AddComponent<SpriteComponent>("Tile/Level1Cube.png", 2);
		pPyramid->AddComponent<LevelComponent>();

		AddGameObject(pPyramid);
	}
	{
		GameObject* pPyramid = new GameObject();
		pPyramid->AddComponent<TransformComponent>(glm::vec3{ 166, 376, 0 });
		pPyramid->AddComponent<RenderableComponent>();
		pPyramid->AddComponent<SpriteComponent>("Tile/Level1Cube.png", 2);
		pPyramid->AddComponent<LevelComponent>();

		AddGameObject(pPyramid);
	}
	{
		GameObject* pPyramid = new GameObject();
		pPyramid->AddComponent<TransformComponent>(glm::vec3{ 197, 376, 0 });
		pPyramid->AddComponent<RenderableComponent>();
		pPyramid->AddComponent<SpriteComponent>("Tile/Level1Cube.png", 2);
		pPyramid->AddComponent<LevelComponent>();

		AddGameObject(pPyramid);
	}

	{
		GameObject* pPyramid = new GameObject();
		pPyramid->AddComponent<TransformComponent>(glm::vec3{ 182, 352, 0 });
		pPyramid->AddComponent<RenderableComponent>();
		pPyramid->AddComponent<SpriteComponent>("Tile/Level1Cube.png", 2);
		pPyramid->AddComponent<LevelComponent>();

		AddGameObject(pPyramid);
	}


	for ( auto o : m_Objects )
	{
		o->Initialize();
	}
}

