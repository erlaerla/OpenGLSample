#include"../Common/Framework.h"

#pragma comment(lib, "Common.lib")
#pragma comment(lib, "Launcher.lib")

class CDrawTriangles : public Framework
{
public:
	CDrawTriangles()
	{

	}

	~CDrawTriangles()
	{

	}

	virtual int		Initialize();
	virtual void	Uninitialize();
	virtual void	Render();
};

static CDrawTriangles app;

int CDrawTriangles::Initialize()
{

	return 0;
}

void CDrawTriangles::Uninitialize()
{

}

void CDrawTriangles::Render()
{

}