#pragma once
#include "Component.h"
#include <string>
#include "Crater/GameObject.h"

namespace CraterEngine
{
	class Font;
	class FPSComponent : public Component
	{
	public:
		FPSComponent(const GameObject* parent);
		virtual ~FPSComponent() override;

	#pragma region deleted
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
	#pragma endregion

		virtual void Update(const float dt) override;
		//virtual void Render() const override;
		virtual bool Initialize() override;

		unsigned int GetCount() const {return m_Count;};
		
	private:
		unsigned int m_Count = 0;
		float m_AccumulatedTimer = 0.0f;
	};
}

