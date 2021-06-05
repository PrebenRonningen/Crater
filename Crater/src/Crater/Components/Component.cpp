#include "CraterPCH.h"
#include "Component.h"
#include "Crater/GameObject.h"

CraterEngine::Component::Component(const GameObject* parent)
	: m_pParent{ parent }
	, m_IsInitialized{ false }
	, m_HasEvent{ false }
{
}

void CraterEngine::Component::NotifyParrent() const
{
	m_pParent->Notify();
}
