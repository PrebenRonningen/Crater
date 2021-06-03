#include "SandBoxPCH.h"
#include "QbertLevelOneScene.h"

using namespace CraterEngine;

QbertLevelOneScene::~QbertLevelOneScene()
{
	m_pPyramid = nullptr;
}

QbertLevelOneScene::QbertLevelOneScene(const std::string& name)
	: Scene(name)
	, m_pPyramid{nullptr}
{
}

void QbertLevelOneScene::Update(const float dt)
{
	for ( auto pO : m_Objects )
	{
		pO->Update(dt);
	}
}

void QbertLevelOneScene::Render() const
{
	for ( auto pO : m_RenderObjects )
	{
		pO->Render();
	}
}

void QbertLevelOneScene::Initialize()
{
	m_pPyramid = new GameObject();
	AddGameObject(m_pPyramid);
}

