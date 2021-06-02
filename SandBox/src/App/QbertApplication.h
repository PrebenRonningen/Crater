#pragma once
#include <CraterEngine.h>

class QbertApplication : public CraterEngine::Crater
{
public:
	QbertApplication()
	{
	}

	virtual void LoadGame() const;
	~QbertApplication()
	{
	}
private:
};