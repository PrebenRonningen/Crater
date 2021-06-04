#pragma once

class ScoreComponent final : public CraterEngine::Component
{
public:
	ScoreComponent(const CraterEngine::GameObject* parent);
	virtual ~ScoreComponent() override
	{
	};

#pragma region deleted
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;
#pragma endregion

	virtual void Update(const float dt) override;
	//virtual void Render() const override;
	virtual bool Initialize() override;

	void Score(){ /* TODO: AddScoreStuff, currently controled bu Oserver and Input*/};

	void AddToScore(int score){m_Score += score; };
	int GetScore() const {return m_Score; };
private:
	int m_Score = 0;
};