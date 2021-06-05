#pragma once
#include <CraterEngine.h>
class QbertComponent : public CraterEngine::Component
{
public:
	QbertComponent(const CraterEngine::GameObject* parent);
	virtual ~QbertComponent() = default;

#pragma region deleted
	QbertComponent(const QbertComponent& other) = delete;
	QbertComponent(QbertComponent&& other) = delete;
	QbertComponent& operator=(const QbertComponent& other) = delete;
	QbertComponent& operator=(QbertComponent&& other) = delete;
#pragma endregion

	virtual void Update(const float dt) override{dt;};
	virtual bool Initialize() override{return true;};
	virtual void Render() const override{};


private:

};

