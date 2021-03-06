#include "SandBoxPCH.h"
#include "SandBoxScene.h"

#include "Commands/LoseLifeCommand.h"
#include "Commands/ScoreCommand.h"
#include "Observers/HealthObserver.h"
#include "Observers/ScoreObserver.h"
#include "Components/HealthComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreDisplayComponent.h"

SandBoxScene::SandBoxScene(const std::string& name)
	:Scene(name)
{
}

void SandBoxScene::Update(const float dt)
{
	for ( auto pO : m_Objects )
	{
		pO->Update(dt);
	}
}

void SandBoxScene::Render() const
{
	for ( auto pO : m_RenderObjects )
	{
		pO->Render();
	}
}

void SandBoxScene::Initialize()
{
		using namespace CraterEngine;
	{
		//Background
		CraterEngine::GameObject* go = new CraterEngine::GameObject;
		go->AddComponent<TransformComponent>();
		go->AddComponent<SpriteComponent>("background.jpg");
		
		RegisterComponentToRender(go->GetComponent<SpriteComponent>());
		AddGameObject(go);
	}
	//{	// Text
	//	GameObject* go = new GameObject();
	//	go->AddComponent<TransformComponent>();
	//	TransformComponent* transformComp = go->GetComponent<TransformComponent>();
	//	go->AddComponent<RenderableComponent>();
	//	RenderableComponent* renderComp = go->GetComponent<RenderableComponent>();
	//	renderComp->SetTextAndColor("Programming 4 Assignment");
	//	auto texInfo = renderComp->GetTexInfo().textureRect;
	//	transformComp->SetPosition(320 - texInfo.w / 2.f, 50, 0);
	//	AddGameObject(go);
	//}
	//{ // Logo
	//	GameObject* go = new GameObject();
	//	go->AddComponent<RenderableComponent>();
	//	RenderableComponent* renderComp = go->GetComponent<RenderableComponent>();
	//	renderComp->SetTexture("logo.png");
	//	auto texInfo = renderComp->GetTexInfo().textureRect;
	//	go->AddComponent<TransformComponent>(glm::vec3{ 320 - texInfo.w / 2.f, 100 - texInfo.h / 2.f, 0 });
	//	
	//	AddGameObject(go);
	//}
	{	// FPS

		CraterEngine::GameObject* go = new CraterEngine::GameObject;
		go->AddComponent<TransformComponent>();
		go->AddComponent<TextComponent>();
		go->AddComponent<FPSComponent>();


		TransformComponent* transformComp = go->GetComponent<TransformComponent>();
		transformComp->SetPosition(20, 20, 0);

		RegisterComponentToRender(go->GetComponent<TextComponent>());
		AddGameObject(go);
	}

	{	// Controls
		CraterEngine::GameObject* controlInfo = new CraterEngine::GameObject();
		controlInfo->AddComponent<TransformComponent>();
		TransformComponent* transformComp = controlInfo->GetComponent<TransformComponent>();
		controlInfo->AddComponent<SpriteComponent>("Controls.png");
		SpriteComponent* pSpriteComp = controlInfo->GetComponent<SpriteComponent>();

		SDL_Rect texInfo = pSpriteComp->GetTexInfo().textureRect;
		transformComp->SetPosition(320.f - texInfo.w / 2.f, 200.f, 0);
		
		RegisterComponentToRender(pSpriteComp);
		AddGameObject(controlInfo);
	}

	{
		CraterEngine::GameObject* qbert = new CraterEngine::GameObject();
		qbert->AddComponent<TransformComponent>(glm::vec3{ 10, 110, 0 });
		qbert->AddComponent<SpriteComponent>("Qbert3.png");
		qbert->AddComponent<HealthComponent>();
		qbert->AddComponent<ScoreComponent>();
		qbert->AddComponent<PlayerComponent>();
		//TODO: InputComponent to easier assign inputs...
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::LShoulder, ButtonState::ButtonDown), new LoseLifeCommand(qbert));

		AddObserver(new ScoreObserver);
		AddObserver(new HealthObserver);
		RegisterComponentToRender(qbert->GetComponent<SpriteComponent>());
		AddGameObject(qbert);

		// DisplayPlayer1Lives

		CraterEngine::GameObject* pPlayerOneLives = new CraterEngine::GameObject();
		pPlayerOneLives->AddComponent<TransformComponent>(glm::vec3(50, 105, 0));
		std::string text =  "Player 1 Lives Left: ";
		SDL_Color color = { 255, 165,0 };
		pPlayerOneLives->AddComponent<TextComponent>(text, color);
		//TextComponent* pTextComp = pPlayerOneLives->GetComponent<TextComponent>();
		//pTextComp->SetTextAndColor();
		pPlayerOneLives->AddComponent<HealthDisplayComponent>(qbert->GetComponent<HealthComponent>());

		RegisterComponentToRender(pPlayerOneLives->GetComponent<TextComponent>());
		AddGameObject(pPlayerOneLives);

		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::DPadLeft, ButtonState::ButtonDown), new ScoreCommand(qbert, ScoreComponent::ScoreEvent::ColorChange));
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::DPadRigh, ButtonState::ButtonDown), new ScoreCommand(qbert, ScoreComponent::ScoreEvent::DefetedCoilyWithFlyingDisc));
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::DPadDown, ButtonState::ButtonDown), new ScoreCommand(qbert, ScoreComponent::ScoreEvent::DiscRemaining));
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::DPadUp, ButtonState::ButtonDown), new ScoreCommand(qbert, ScoreComponent::ScoreEvent::CaughtSam));

		//	DisplayScore
		CraterEngine::GameObject* pPlayerOneScore = new CraterEngine::GameObject();
		pPlayerOneScore->AddComponent<TransformComponent>(glm::vec3(50, 150, 0));
		text = "Player 1 Lives Left: ";
		pPlayerOneScore->AddComponent<TextComponent>(text, color);
		pPlayerOneScore->AddComponent<ScoreDisplayComponent>(qbert->GetComponent<ScoreComponent>());

		RegisterComponentToRender(pPlayerOneScore->GetComponent<TextComponent>());
		AddGameObject(pPlayerOneScore);
	}

	{	// Player 2
		CraterEngine::GameObject* qbert = new CraterEngine::GameObject();
		qbert->AddComponent<TransformComponent>(glm::vec3{ 250, 10, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 5, 5, 1});
		qbert->AddComponent<SpriteComponent>("Qbert3.png", 2, 2);
		qbert->AddComponent<HealthComponent>();
		qbert->AddComponent<ScoreComponent>();
		qbert->AddComponent<PlayerComponent>();
		//TODO: InputComponent to easier assign inputs...

		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::RShoulder, ButtonState::ButtonDown), new LoseLifeCommand(qbert));

		RegisterComponentToRender(qbert->GetComponent<SpriteComponent>());
		AddGameObject(qbert);

		// DisplayPlayer2Lives

		CraterEngine::GameObject* pPlayerTwoLives = new CraterEngine::GameObject();
		pPlayerTwoLives->AddComponent<TransformComponent>(glm::vec3(320, 5, 0));
		std::string text = "Player 2 Lives Left: ";
		SDL_Color color = { 165, 255, 0 };
		pPlayerTwoLives->AddComponent<TextComponent>(text, color);
		pPlayerTwoLives->AddComponent<HealthDisplayComponent>(qbert->GetComponent<HealthComponent>());

		RegisterComponentToRender(pPlayerTwoLives->GetComponent<TextComponent>());
		AddGameObject(pPlayerTwoLives);

		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonA, ButtonState::ButtonDown), new ScoreCommand(qbert, ScoreComponent::ScoreEvent::ColorChange));
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonB, ButtonState::ButtonDown), new ScoreCommand(qbert, ScoreComponent::ScoreEvent::DefetedCoilyWithFlyingDisc));
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonX, ButtonState::ButtonUp), new ScoreCommand(qbert, ScoreComponent::ScoreEvent::DiscRemaining));
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonY, ButtonState::ButtonDown), new ScoreCommand(qbert, ScoreComponent::ScoreEvent::CaughtSam));

		//	DisplayScore
		CraterEngine::GameObject* pPlayerTwoScore = new CraterEngine::GameObject();
		pPlayerTwoScore->AddComponent<TransformComponent>(glm::vec3(320, 50, 0));
		text = "Player 2 Score: ";
		pPlayerTwoScore->AddComponent<TextComponent>(text, color);

		pPlayerTwoScore->AddComponent<ScoreDisplayComponent>(qbert->GetComponent<ScoreComponent>());

		RegisterComponentToRender(pPlayerTwoScore->GetComponent<TextComponent>());
		AddGameObject(pPlayerTwoScore);
	}

	for ( auto o : m_Objects )
	{
		o->Initialize();
	}
}
