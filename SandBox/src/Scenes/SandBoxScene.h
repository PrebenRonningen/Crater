#pragma once
#include <CraterEngine.h>

class SandBoxScene final : public CraterEngine::Scene
{
public:
	virtual ~SandBoxScene() = default;

	explicit SandBoxScene(const std::string& name);
	SandBoxScene(const SandBoxScene& other) = delete;
	SandBoxScene(SandBoxScene&& other) = delete;
	SandBoxScene& operator=(const SandBoxScene& other) = delete;
	SandBoxScene& operator=(SandBoxScene&& other) = delete;

	virtual void Update(const float dt);
	virtual void Render() const;
	virtual void Initialize();
private:

};

