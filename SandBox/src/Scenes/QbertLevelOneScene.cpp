#include "SandBoxPCH.h"
#include "Crater/Managers/ResourceManager.h"
#include "QbertLevelOneScene.h"
#include "Components/LevelComponent.h"
#include "Components/QbertComponent.h"
#include "Components/MovementComponent.h"
#include "Observers/LevelObserver.h"
#include "Commands/MoveUpLeftCommand.h"
#include "Commands/MoveUpRightCommand.h"
#include "Commands/MoveDownLeftCommand.h"
#include "Commands/MoveDownRightCommand.h"

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
		m_pPyramid->AddComponent<SpriteComponent>("Tile/Level1Cube.png", 2);
		m_pPyramid->AddComponent<LevelComponent>(7);

		// TODO: Add Level Observer for Qbert to notify that it has moved
		RegisterComponentToRender(m_pPyramid->GetComponent<LevelComponent>());
		AddGameObject(m_pPyramid);

		AddObserver(new LevelObserver(m_pPyramid->GetComponent<LevelComponent>()));
	}
	{
		GameObject* qBert = new GameObject();
		qBert->AddComponent<TransformComponent>(m_pPyramid->GetComponent<LevelComponent>()->GetSpawnPos(), glm::vec3{ 0,0,0 }, glm::vec3{ 2,2,2 });
		qBert->AddComponent<SpriteComponent>("Qbert/Qbert.png", 1, 8);
		qBert->AddComponent<QbertComponent>(m_pPyramid->GetComponent<LevelComponent>());
		qBert->AddComponent<MovementComponent>(m_pPyramid->GetComponent<LevelComponent>());
		m_qSprite = qBert->GetComponent<SpriteComponent>();
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonX, CraterEngine::ButtonState::ButtonUp), new MoveUpLeftCommand(qBert));
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonY, CraterEngine::ButtonState::ButtonUp), new MoveUpRightCommand(qBert));
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonA, CraterEngine::ButtonState::ButtonUp), new MoveDownLeftCommand(qBert));
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonB, CraterEngine::ButtonState::ButtonUp), new MoveDownRightCommand(qBert));

		RegisterComponentToRender(qBert->GetComponent<SpriteComponent>());
		m_pPyramid->GetComponent<LevelComponent>()->RegisterPlayer(qBert->GetComponent<QbertComponent>());
		AddGameObject(qBert);
	}
	//pos is +208x = 3*64 + 16
	//pos is -304y = 6*48 + 16

	for ( auto o : m_Objects )
	{
		o->Initialize();
	}
}

