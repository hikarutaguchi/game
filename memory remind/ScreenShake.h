#pragma once
#include "VECTOR2.h"

#define lpScreenShake ScreenShake::GetInstance()
class ScreenShake
{
public:
	static ScreenShake &GetInstance(void)
	{
		static ScreenShake s_instance;
		return s_instance;
	}
	ScreenShake();
	~ScreenShake();
	void UpData();
	void SetShake(int ShakeSize, int ShakeTime);
	VECTOR2 SetPos();
private:
	int Init();
	bool shakeFlag;		//揺れたかどうか
	int shakeSize;		//揺れる大きさ
	int shakeTime;		//揺れる時間
	VECTOR2 pos;		//揺らしたい画像に渡す値
	VECTOR2 tmpPos;		//保存用	
};
