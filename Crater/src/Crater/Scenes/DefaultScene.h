#pragma once
#include "Scene.h"

namespace CraterEngine
{
	class DefaultScene final : public Scene
	{
	public:
		virtual ~DefaultScene(){};

		explicit DefaultScene(const std::string& name);
		DefaultScene(const DefaultScene& other) = delete;
		DefaultScene(DefaultScene&& other) = delete;
		DefaultScene& operator=(const DefaultScene& other) = delete;
		DefaultScene& operator=(DefaultScene&& other) = delete;

		virtual void Update(const float dt);
		virtual void Render() const;
		virtual void Initialize();

	private:
	};


}