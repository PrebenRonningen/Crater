#pragma once
#include <vector>
#include "Crater/Events/Event.h"

namespace CraterEngine
{
	class Observer;
	class GameObject;
	class Subject
	{
	public:
		Subject() = default;
		~Subject();

		#pragma region deleted
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) noexcept = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) noexcept = delete;
		#pragma endregion

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

		void Notify(const GameObject* object);

	protected:
	
	private:
		std::vector<Observer*> m_Observers;

	};
}