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
	bool shakeFlag;		//—h‚ê‚½‚©‚Ç‚¤‚©
	int shakeSize;		//—h‚ê‚é‘å‚«‚³
	int shakeTime;		//—h‚ê‚éŽžŠÔ
	VECTOR2 pos;		//—h‚ç‚µ‚½‚¢‰æ‘œ‚É“n‚·’l
	VECTOR2 tmpPos;		//•Û‘¶—p	
};
