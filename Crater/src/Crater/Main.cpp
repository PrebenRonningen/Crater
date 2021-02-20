#include "CraterPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Crater.h"

int main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;

	CraterEngine::Crater engine;
	engine.Run();
	
	return 0;
}