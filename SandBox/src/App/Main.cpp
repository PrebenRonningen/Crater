#include "SandBoxPCH.h"
#include "QbertApplication.h"
#include "SandBox.h"


int main(int, char* [])
{
	//QbertApplication* eng = new QbertApplication();
	Sandbox* eng = new Sandbox();
	srand(unsigned int(std::time(0)));
	eng->Run();
	if ( eng )
	{
		delete eng;
		eng = nullptr;
	}

	return 0;
}