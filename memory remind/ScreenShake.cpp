#include "DxLib.h"
#include "ScreenShake.h"



ScreenShake::ScreenShake()
{
	Init();
}


ScreenShake::~ScreenShake()
{
}

void ScreenShake::UpData()
{
	if (shakeFlag)
	{
		pos = tmpPos;

		shakeTime--;

		if (shakeTime == 0)
		{
			shakeFlag = false;
		}

		pos.x += GetRand(shakeSize + shakeTime);
		pos.x -= GetRand(shakeSize + shakeTime);
		pos.y += GetRand(shakeSize + shakeTime);
		pos.y -= GetRand(shakeSize + shakeTime);
	}
}

void ScreenShake::SetShake(int ShakeSize, int ShakeTime)
{
	this->shakeTime = ShakeTime;
	this->shakeSize = ShakeSize;
	shakeFlag = true;
}

VECTOR2 ScreenShake::SetPos()
{
	return pos;
}

int ScreenShake::Init()
{
	tmpPos = { 0,0 };
	shakeTime = 0;
	pos = { 0,0 };
	shakeFlag = false;
	return 0;
}
