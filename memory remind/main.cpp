using namespace std;
#include <stdlib.h>
#include "Dxlib.h"	// DxLib×²ÌŞ×Ø‚ğg—p‚·‚é
#include "SceneMng.h"

// ---------- WinMainŠÖ”
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SceneMng::GetInstance().Run();

	DxLib_End();	// DX×²ÌŞ×Ø‚ÌI—¹ˆ—
	return 0;
}

bool SysInit(void)
{
	return true;
}
void Destroy(void)
{
}
