#pragma once
#include <CraterEngine.h>
class LevelComponent;
class QbertComponent : public CraterEngine::Component
{
public:
	QbertComponent(const CraterEngine::GameObject* parent, LevelComponent* levelComponent);
	virtual ~QbertComponent() = default;

#pragma region deleted
	QbertComponent(const QbertComponent& other) = delete;
	QbertComponent(QbertComponent&& other) = delete;
	QbertComponent& operator=(const QbertComponent& other) = delete;
	QbertComponent& operator=(QbertComponent&& other) = delete;
#pragma endregion

	virtual void Update(const float dt) override;
	virtual bool Initialize() override;
	virtual void Render() const override{};

private:
	float m_Time;
	float m_NeededTime;
	LevelComponent* m_LevelComponent;
	CraterEngine::SpriteComponent* m_pSprite;
};

