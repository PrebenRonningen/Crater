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

	//void DefaultScene::Update(const float dt)
	//{
	//	for ( auto pO : m_Objects )
	//	{
	//		pO->Update(dt);
	//	}
	//}

	//void DefaultScene::Render() const
	//{
	//	for ( auto pO : m_RenderObjects )
	//	{
	//		pO->Render();
	//	}
	//}

	void DefaultScene::Initialize()
	{
		{
			//Background
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			SpriteComponent* pSpriteComp = go->GetComponent<SpriteComponent>();
			pSpriteComp->SetTexture("background.jpg");

			RegisterComponentToRender(pSpriteComp);
			AddGameObject(go);
		}
		{	// Text
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			go->AddComponent<TextComponent>();
			TextComponent* pTextComp = go->GetComponent<TextComponent>();
			pTextComp->SetText("Programming 4 Assignment");

			SDL_Rect texInfo = pTextComp->GetTexInfo().textureRect;
			transformComp->SetPosition(320 - texInfo.w / 2.f, 150, 0);
			
			RegisterComponentToRender(pTextComp);
			AddGameObject(go);
		}
		{ // Logo
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			go->AddComponent<SpriteComponent>();
			SpriteComponent* pSpriteComp = go->GetComponent<SpriteComponent>();
			pSpriteComp->SetTexture("logo.png");
			auto texInfo = pSpriteComp->GetTexInfo().textureRect;

			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			transformComp->SetPosition(320 - texInfo.w / 2.f, 220 - texInfo.h / 2.f, 0);

			RegisterComponentToRender(pSpriteComp);
			AddGameObject(go);
		}
		{	// FPS
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			transformComp->SetPosition(20, 20, 0);
			go->AddComponent<TextComponent>();
			go->AddComponent<FPSComponent>();

			RegisterComponentToRender(go->GetComponent<TextComponent>());
			AddGameObject(go);
		}

		for ( auto pO : m_Objects )
		{
			pO->Initialize();
		}
	}
}