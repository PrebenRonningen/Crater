#pragma once

namespace CraterEngine
{
	class GameObject;
	class Component
	{
	public:
		Component(const GameObject* parent) ;

		virtual ~Component() = default;

	#pragma region deleted
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	#pragma endregion
		
		virtual bool Initialize() = 0;
		virtual void Update(const float dt) = 0;
		virtual void Render() const{};

		bool IsInitialized() { return m_IsInitialized; };
	
		void EventHandeled(){m_HasEvent = false;}
		bool HasEvent() const { return m_HasEvent; }
		void NotifyParrent() const;
	protected:
		bool m_HasEvent;
		bool m_IsInitialized;
		const GameObject* m_pParent{};
	};

}

