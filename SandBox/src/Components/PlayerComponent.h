#pragma once


class CraterEngine::GameObject;
class PlayerComponent final : public CraterEngine::Component
{
public:

	PlayerComponent(const CraterEngine::GameObject* parent);
	virtual ~PlayerComponent() override;

#pragma region deleted
	PlayerComponent(const PlayerComponent& other) = delete;
	PlayerComponent(PlayerComponent&& other) noexcept = delete;
	PlayerComponent& operator=(const PlayerComponent& other) = delete;
	PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;
#pragma endregion

	virtual void Update(const float dt) override{dt;};
	virtual bool Initialize() override{return true;};
	std::uint8_t GetPlayerID() const {return m_PlayerID;};

private:
	// TODO: make less bad...
	// this will currently assign the wrong ID.
	// if 3 players, player 1 get's destroyed, new player enters, there can now 2 players with the same ID.
	std::uint8_t m_PlayerID = 0;
	static std::uint8_t m_TotalPlayerCount;
};

