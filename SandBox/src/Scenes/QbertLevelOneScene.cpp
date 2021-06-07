#include "SandBoxPCH.h"
#include "Crater/Managers/ResourceManager.h"
#include "QbertLevelOneScene.h"
#include "Components/LevelComponent.h"
#include "Components/QbertComponent.h"
#include "Components/MovementComponent.h"
#include "Observers/ScoreObserver.h"
#include "Observers/HealthObserver.h"
#include "Observers/LevelObserver.h"
#include "Commands/MoveUpLeftCommand.h"
#include "Commands/MoveUpRightCommand.h"
#include "Commands/MoveDownLeftCommand.h"
#include "Commands/MoveDownRightCommand.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Components/HealthComponent.h"
#include "Components/HealthDisplayComponent.h"

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
	//	ResourceManager::GetInstance().Init("../Crater/Data/");
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
		qBert->AddComponent<ScoreComponent>();
		qBert->AddComponent<HealthComponent>();

		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonX, CraterEngine::ButtonState::ButtonUp), new MoveUpLeftCommand(qBert));
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonY, CraterEngine::ButtonState::ButtonUp), new MoveUpRightCommand(qBert));
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonA, CraterEngine::ButtonState::ButtonUp), new MoveDownLeftCommand(qBert));
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonB, CraterEngine::ButtonState::ButtonUp), new MoveDownRightCommand(qBert));


		RegisterComponentToRender(qBert->GetComponent<SpriteComponent>());
		m_pPyramid->GetComponent<LevelComponent>()->RegisterPlayer(qBert);
		AddGameObject(qBert);

		// DisplayPlayer1Lives

		GameObject* pPlayerOneLives = new GameObject();
		pPlayerOneLives->AddComponent<TransformComponent>(glm::vec3(10, 75, 0), glm::vec3(0, 0, 0), glm::vec3(1.5f, 1.5f, 1.5f));
		pPlayerOneLives->AddComponent<SpriteComponent>("Qbert/Qbert.png",1,8);
		pPlayerOneLives->AddComponent<HealthDisplayComponent>(qBert->GetComponent<HealthComponent>());

		RegisterComponentToRender(pPlayerOneLives->GetComponent<HealthDisplayComponent>());
		AddGameObject(pPlayerOneLives);
		AddObserver(new HealthObserver());


		ResourceManager::GetInstance().Init("../Crater/Data/");
		// Player 1 UI

		GameObject* pPlayerUItext = new GameObject();
		pPlayerUItext->AddComponent<TransformComponent>(glm::vec3{ 55,20,0 });
		std::string text = "Player: ";
		SDL_Color color = { 165, 255, 0 };
		int fontSize = 20;
		pPlayerUItext->AddComponent<TextComponent>(text, color, fontSize);
		ResourceManager::GetInstance().Init("../SandBox/Resources/Images/");
		TextComponent* pTextComp = pPlayerUItext->GetComponent<TextComponent>();
	
		RegisterComponentToRender(pTextComp);
		AddGameObject(pPlayerUItext);


		GameObject* pPlayerUInumber = new GameObject();
		auto textPosition = pTextComp->GetTexInfo().destinationRectangle;
		pPlayerUInumber->AddComponent<TransformComponent>(glm::vec3{ textPosition.x + textPosition.w ,textPosition.y,0 }, glm::vec3{0,0,0}, glm::vec3{2,2,2});
		pPlayerUInumber->AddComponent<SpriteComponent>("Tile/PlayerIndicator.png", 1, 2);
		SpriteComponent* pSpriteComp = pPlayerUInumber->GetComponent<SpriteComponent>();

		RegisterComponentToRender(pSpriteComp);
		AddGameObject(pPlayerUInumber);


		//	DisplayScore
		ResourceManager::GetInstance().Init("../Crater/Data/");
		GameObject* pPlayerOneScore = new GameObject();
		pPlayerOneScore->AddComponent<TransformComponent>(glm::vec3(50, textPosition.y + textPosition.h * 1.25f , 0));
		text = "";
		color.r = 255;
		color.g = 150;
		pPlayerOneScore->AddComponent<TextComponent>(text, color, fontSize);
		pPlayerOneScore->AddComponent<ScoreDisplayComponent>(qBert->GetComponent<ScoreComponent>());

		AddObserver(new ScoreObserver);

		RegisterComponentToRender(pPlayerOneScore->GetComponent<TextComponent>());
		AddGameObject(pPlayerOneScore);


		// Change To text
		GameObject* pChangeToText = new GameObject();
		pChangeToText->AddComponent<TransformComponent>(glm::vec3(55, textPosition.y + textPosition.h * 2.25f, 0));
		text = "Change To:";
		color.r = 155;
		color.g = 50;

		pChangeToText->AddComponent<TextComponent>(text, color, fontSize);
		RegisterComponentToRender(pChangeToText->GetComponent<TextComponent>());
		AddGameObject(pChangeToText);
		//Change To Block

		textPosition = pChangeToText->GetComponent<TextComponent>()->GetTexInfo().destinationRectangle;
		ResourceManager::GetInstance().Init("../SandBox/Resources/Images/");
		GameObject* pChangeToBlock = new GameObject();
		pChangeToBlock->AddComponent<TransformComponent>(glm::vec3(textPosition.x + textPosition.w/3.f, textPosition.y + textPosition.h * 1.25f, 0), glm::vec3{ 0,0,0 }, glm::vec3{ 2,2,2 });
		pChangeToBlock->AddComponent<SpriteComponent>("Tile/Level1ChangeToCube.png");

		RegisterComponentToRender(pChangeToBlock->GetComponent<SpriteComponent>());
		AddGameObject(pChangeToBlock);
	}

	ResourceManager::GetInstance().Init("../Crater/Data/");
	for ( auto o : m_Objects )
	{
		o->Initialize();
	}
}

