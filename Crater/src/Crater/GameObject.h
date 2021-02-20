#pragma once
#include <typeinfo>
#include "Crater/Components/TransformComponent.h"
#include "SceneObject.h"
#include "Components/Component.h"

namespace CraterEngine
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		GameObject()
		{
		};
		virtual ~GameObject();

		virtual void Update(const float dt) override;
		virtual void Render() const override;
		void Initialize();

	#pragma region deleted
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	#pragma endregion
		
		template <class T>
		void AddComponent()
		{
			//if ( typeid( T ) == typeid( Component) )
			//{

				m_Components.push_back(new T{ this });
			//}
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

	private:
		std::vector<Component*> m_Components{};
	};
}

