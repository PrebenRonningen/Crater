#pragma once
namespace CraterEngine
{
	class SceneObject
	{
	public:
		virtual void Update(const float dt) = 0;
		virtual void Render() const = 0;
		virtual void Initialize() = 0;
		SceneObject() = default;
		virtual ~SceneObject() {};
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}