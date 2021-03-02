#include "CraterPCH.h"
#include "Subject.h"
#include "Observer.h"
#include "Crater/GameObject.h"
#include <typeinfo>
#include <cassert>

namespace CraterEngine
{
	Subject::~Subject()
	{
		for ( Observer* observer : m_Observers )
		{
			if ( observer )
			{
				delete observer;
				observer = nullptr;
			}
		}
	}
	
	void Subject::AddObserver(Observer* observer)
	{
		for ( Observer* pObs : m_Observers )
		{
			pObs;
			assert(typeid(*pObs) != typeid( *observer ) && "Observer exists");
		}
	
		m_Observers.push_back(observer);
	}
	
	void Subject::RemoveObserver(Observer* observer)
	{
		std::vector<Observer*>::iterator it = std::find(m_Observers.begin(), m_Observers.end(), observer);
		if ( it != m_Observers.end() )
		{
			m_Observers.erase(it);
		}
	}
	
	void Subject::Notify(const GameObject& object, const EventType& event)
	{
		for ( Observer* pObs : m_Observers )
		{
			pObs->OnNotify(object, event);
		}
	}
}