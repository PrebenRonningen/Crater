#include <CraterPCH.h>
#include <CraterEngine.h>

class Sandbox : public CraterEngine::Crater
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};



int main(int , char* [])
{
	Sandbox* eng = new Sandbox();
	
	eng->Run();

	delete eng;
	eng = nullptr;

	return 0;
}