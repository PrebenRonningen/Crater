#pragma once
#include <CraterEngine.h>

class QbertLevelOneScene final : public CraterEngine::Scene
{
public:
	explicit QbertLevelOneScene(const std::string& name);
	virtual ~QbertLevelOneScene() override;

#pragma region deleted
	QbertLevelOneScene(const QbertLevelOneScene& other) = delete;
	QbertLevelOneScene(QbertLevelOneScene&& other) = delete;
	QbertLevelOneScene& operator=(const QbertLevelOneScene& other) = delete;
	QbertLevelOneScene& operator=(QbertLevelOneScene&& other) = delete;
#pragma endregion

	virtual void Update(const float dt);
	virtual void Render() const;
	virtual void Initialize();
private:

	float time = 0;
	float neededTime = 1;

	CraterEngine::SpriteComponent* qSprite;
	CraterEngine::GameObject* m_pPyramid;
};
