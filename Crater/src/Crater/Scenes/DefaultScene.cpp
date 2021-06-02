#include "CraterPCH.h"
#include "DefaultScene.h"
#include "Crater/GameObject.h"
#include "Crater/Components/CoreComponents.h"
namespace CraterEngine
{

	DefaultScene::DefaultScene(const std::string& name)
		: Scene(name)
	{
	}

	void DefaultScene::Update(const float dt)
	{
		for ( auto pO : m_Objects )
		{
			pO->Update(dt);
		}
	}

	void DefaultScene::Render() const
	{
		for ( auto pO : m_RenderObjects )
		{
			pO->Render();
		}
	}

	void DefaultScene::Initialize()
	{
		{
			//Background
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			go->AddComponent<RenderableComponent>();
			RenderableComponent* rendererComp = go->GetComponent<RenderableComponent>();
			rendererComp->SetTexture("background.jpg");
			AddGameObject(go);
		}
		{	// Text
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			go->AddComponent<RenderableComponent>();
			RenderableComponent* renderComp = go->GetComponent<RenderableComponent>();
			renderComp->SetTextAndColor("Programming 4 Assignment");
			auto texInfo = renderComp->GetTexInfo().textureRect;
			transformComp->SetPosition(320 - texInfo.w / 2.f, 150, 0);
			AddGameObject(go);
		}
		{ // Logo
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			go->AddComponent<RenderableComponent>();

			RenderableComponent* renderComp = go->GetComponent<RenderableComponent>();
			renderComp->SetTexture("logo.png");
			auto texInfo = renderComp->GetTexInfo().textureRect;

			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			transformComp->SetPosition(320 - texInfo.w / 2.f, 220 - texInfo.h / 2.f, 0);
			AddGameObject(go);
		}
		{	// FPS
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			transformComp->SetPosition(20, 20, 0);
			go->AddComponent<RenderableComponent>();
			go->AddComponent<FPSComponent>();
			AddGameObject(go);
		}

		for ( auto pO : m_Objects )
		{
			pO->Initialize();
		}
	}
}