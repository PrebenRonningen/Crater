#pragma once
#include "Crater/Events/Event.h"
namespace CraterEngine
{
	class GameObject;
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer(){};

		#pragma region deleted
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) noexcept = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) noexcept = delete;
		#pragma endregion

		virtual void OnNotify(const GameObject* object) = 0;
	};
}