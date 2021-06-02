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

void QbertLevelOneScene::Initialize()
{
	m_pPyramid = new GameObject();
	AddGameObject(m_pPyramid);


}

