#include "CraterPCH.h"
#include "GameObject.h"
#include "Crater/Managers/ResourceManager.h"
#include "Renderer.h"
#include "Components/CoreComponents.h"
#include "Crater/Events/Event.h"
#include "Crater/Observer/Subject.h"

namespace CraterEngine
{
	GameObject::~GameObject()
	{
		for ( Component* comp : m_Components )
		{	
			delete comp;
			comp = nullptr;
		}
	};

	void GameObject::Update( const float dt )
	{
		for ( Component* comp : m_Components )
		{
			comp->Update(dt);
		}
	}

	void GameObject::Render() const
	{
		//GetComponent<RenderableComponent>()->Render();
		//for ( Component* comp : m_Components )
		//{
		//	comp->Render();
		//}
	}

	void GameObject::Initialize()
	{
		for ( Component* comp : m_Components )
		{
			if(!comp->IsInitialized() )
				comp->Initialize();
		}
	}
	void GameObject::Notify() const
	{
		m_pSubject->Notify(this);
	}

}