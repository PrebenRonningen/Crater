#include "CraterPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Crater.h"

int main(int, char* [])
{
	CraterEngine::Crater engine;
	engine.Run();
	return 0;
}