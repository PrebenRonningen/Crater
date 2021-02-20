#include "CraterPCH.h"
#include "Scene.h"
#include "GameObject.h"

namespace CraterEngine
{
	unsigned int Scene::m_IdCounter = 0;

	Scene::Scene(const std::string& name) : m_Name(name)
	{
	}

	Scene::~Scene()
	{
		for ( SceneObject* obj : m_Objects )
		{
			delete obj;
			obj = nullptr;
		}
		m_Objects.clear();
	}

	void Scene::Add(SceneObject* object)
	{
		m_Objects.push_back(object);
	}

	void Scene::Update(const float dt)
	{
		for ( auto& object : m_Objects )
		{
			object->Update(dt);
		}
	}

	void Scene::Render() const
	{
		for ( const auto& object : m_Objects )
		{
			object->Render();
		}
	}
	void Scene::Initialize()
	{
		for ( auto& object : m_Objects )
		{
			object->Initialize();
		}
	}
}