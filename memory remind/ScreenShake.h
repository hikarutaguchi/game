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
	bool shakeFlag;		//�h�ꂽ���ǂ���
	int shakeSize;		//�h���傫��
	int shakeTime;		//�h��鎞��
	VECTOR2 pos;		//�h�炵�����摜�ɓn���l
	VECTOR2 tmpPos;		//�ۑ��p	
};
