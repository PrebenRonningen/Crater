#include "CraterPCH.h"
#include "FPSComponent.h"
#include "Crater/Components/TextComponent.h"
#include <string>

namespace CraterEngine
{
	FPSComponent::FPSComponent(const GameObject* parent)
		: Component(parent)
		, m_Count{0}
		, m_AccumulatedTimer{0}
	{
	}

	FPSComponent::~FPSComponent()
	{
		//delete m_pText;
		//m_pText = nullptr;
	}

	void FPSComponent::Update(const float dt)
	{
		m_Count++;
		m_AccumulatedTimer += dt;
	
		if ( m_AccumulatedTimer >= 1.0f )
		{
			//m_pText->SetText(std::to_string(1.f/dt));
			//m_pText->Update(dt);
			const auto& renderable = m_pParent->GetComponent<TextComponent>();
			renderable->SetText(std::to_string(m_Count));

			m_AccumulatedTimer -= 1;
			m_Count = 0;
		}
	}

	//void FPSComponent::Render() const
	//{
	//	//Transform* trandform = m_pParent->GetComponent<Transform>();
	//	//m_pText->Render(trandform->GetPosition().x, trandform->GetPosition().y);
	//}

	bool FPSComponent::Initialize()
	{
		if( m_IsInitialized ) return true;
		m_Count = 0;
		m_AccumulatedTimer = 0;

		const auto& renderable = m_pParent->GetComponent<TextComponent>();
		renderable->SetTextAndColor(std::to_string(m_Count), {0, 230, 0});

		renderable->Initialize();
		m_IsInitialized = true;
		return true;
	}

}