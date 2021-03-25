#pragma once
#include <typeinfo>
#include "Crater/Components/TransformComponent.h"
#include "Components/Component.h"
#include "Events/Event.h"
class Subject;

namespace CraterEngine
{
	class Subject;
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject(){};
		~GameObject();

		void Update(const float dt);
		void Render() const;
		void Initialize();

	#pragma region deleted
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	#pragma endregion
		
		template <class T, typename... Args>
		void AddComponent(Args... args)
		{
			m_Components.push_back(new T{ this, args... });
		}

		template <class T>
		T* GetComponent() const
		{
			const type_info& ti = typeid( T );
			for ( auto* component : m_Components )
			{
				if ( component && typeid( *component ) == ti )
					return static_cast<T*>( component );
			}
			return nullptr;
		}

		template <typename T>
		bool HasComponent()
		{
			for ( auto* component : m_Components )
			{
				if ( typeid( *component ) == typeid( T ) ) return true;
			}
			return false;
		}

		void Notify(const GameObject& object, const CraterEngine::EventType& event) const;
		
		void SetSubject(Subject* subject)
		{
			if ( m_pSubject == nullptr )
				m_pSubject = subject;
		};

	private:
		std::vector<Component*> m_Components{};
		// turn into component
		Subject* m_pSubject = nullptr;

	};
}

