#include "SandBoxPCH.h"
#include "QbertApplication.h"
#include "SandBox.h"

int main(int, char* [])
{
	QbertApplication* eng = new QbertApplication();

	eng->Run();
	if ( eng )
	{
		delete eng;
		eng = nullptr;
	}

	return 0;
}