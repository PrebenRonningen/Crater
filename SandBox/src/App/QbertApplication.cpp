#include "SandBoxPCH.h"
#include <CraterEngine.h>
#include "QbertApplication.h"
#include "Scenes/QbertLevelOneScene.h"

void QbertApplication::LoadGame() const
{
	QbertLevelOneScene& scene = CraterEngine::SceneManager::GetInstance().CreateScene<QbertLevelOneScene>("Level1");
	//QbertLevelOneScene& scene = CraterEngine::SceneManager::GetInstance().CreateScene<QbertLevelTwoScene>("Level2");
	//QbertLevelOneScene& scene = CraterEngine::SceneManager::GetInstance().CreateScene<QbertLevelThreeScene>("Level3");

	scene.Initialize();
}
