#pragma once
#include <CraterEngine.h>
class LevelComponent;
class LevelObserver : public CraterEngine::Observer
{
public:
	LevelObserver(LevelComponent* levelComponent);
	virtual ~LevelObserver() override
	{
	};

#pragma region deleted
	LevelObserver(const LevelObserver& other) = delete;
	LevelObserver(LevelObserver&& other) noexcept = delete;
	LevelObserver& operator=(const LevelObserver& other) = delete;
	LevelObserver& operator=(LevelObserver&& other) noexcept = delete;
#pragma endregion

	virtual void OnNotify(const CraterEngine::GameObject* pObject) override;
private:
	LevelComponent* m_Level;
};

