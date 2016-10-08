#include <stdio.h>
#include"../Common/Framework.h"

#pragma comment(lib, "Common.lib")

int main(int argc, char* argv[])
{
	Framework *pFramework = Framework::GetSingletonPtr();
	if (0 == pFramework)
	{
		return 0;
	}

	if (0 != pFramework->Startup())
	{
		return 0;
	}

	pFramework->Loop();

	pFramework->Shutdown();

	return 0;
}