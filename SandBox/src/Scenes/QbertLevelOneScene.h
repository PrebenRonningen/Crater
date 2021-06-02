#pragma once
#include <CraterEngine.h>

class QbertLevelOneScene : public CraterEngine::Scene
{
public:
	virtual ~QbertLevelOneScene() override;

	explicit QbertLevelOneScene(const std::string& name);
	QbertLevelOneScene(const QbertLevelOneScene& other) = delete;
	QbertLevelOneScene(QbertLevelOneScene&& other) = delete;
	QbertLevelOneScene& operator=(const QbertLevelOneScene& other) = delete;
	QbertLevelOneScene& operator=(QbertLevelOneScene&& other) = delete;

	virtual void Update(const float dt);
	virtual void Render() const;
	virtual void Initialize();
private:
	CraterEngine::GameObject* m_pPyramid;
};
