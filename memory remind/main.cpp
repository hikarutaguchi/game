using namespace std;
#include <stdlib.h>
#include "Dxlib.h"	// DxLibײ���؂��g�p����
#include "SceneMng.h"

// ---------- WinMain�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SceneMng::GetInstance().Run();
	DxLib_End();	// DXײ���؂̏I������
	return 0;
}

void Destroy(void)
{
}