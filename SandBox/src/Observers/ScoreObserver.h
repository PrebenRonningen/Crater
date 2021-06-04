#pragma once
#include "CraterEngine.h"
#include <tuple>

class ScoreObserver final : public CraterEngine::Observer
{
public:
	ScoreObserver() = default;
	virtual ~ScoreObserver() override
	{
	};

#pragma region deleted
	ScoreObserver(const ScoreObserver& other) = delete;
	ScoreObserver(ScoreObserver&& other) noexcept = delete;
	ScoreObserver& operator=(const ScoreObserver& other) = delete;
	ScoreObserver& operator=(ScoreObserver&& other) noexcept = delete;
#pragma endregion

	virtual void OnNotify(const CraterEngine::GameObject & object, const CraterEngine::EventType & event) override;
	int GetScore(int id) const{return m_Score[id];};
private:
	std::vector<int> m_Ids;
	std::vector<int> m_Score{4};
};

