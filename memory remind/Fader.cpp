#include "Fader.h"
#include <DxLib.h>

Fader::Fader()
{
	Init();
}

Fader::~Fader()
{
}

void Fader::Updata()
{
	switch (fadeState)
	{
	case FADE_IN_START:
		if (fadeInFlag == true)
		{
			brightness += fadeSpeed;
			if (brightness <= 255)
			{
				//�ŏ��l����brightness���v���X
				SetDrawBright(brightness, brightness, brightness);
			}
			else
			{
				//�ő�l���Z�b�g���Ď��Ɉڍs
				SetDrawBright(255, 255, 255);
				brightness = 0;
				fadeState = FADE_IN_END;
			}
		}
		break;
	case FADE_IN_END:
		fadeInFlag = false;
		break;
	case FADE_OUT_START:
		if (fadeOutFlag == true)
		{
			brightness += fadeSpeed;
			if (brightness <= 255)
			{
				//�ő�l����brightness���}�C�i�X
				SetDrawBright(255 - brightness, 255 - brightness, 255 - brightness);
			}
			else
			{
				//�ŏ��l���Z�b�g���Ď��Ɉڍs
				SetDrawBright(0, 0, 0);
				brightness = 0;
				fadeState = FADE_OUT_END;
			}
		}
		break;
	case FADE_OUT_END:
		fadeOutFlag = false;
		break;
	case FADE_WAIT:
		break;
	default:
		break;
	}
}

void Fader::SetFadeIn(int fadeSpeed)
{
	this->fadeSpeed = fadeSpeed;
	fadeInFlag = true;
	fadeState = FADE_IN_START;
}

void Fader::SetFadeOut(int fadeSpeed)
{
	this->fadeSpeed = fadeSpeed;
	fadeOutFlag = true;
	fadeState = FADE_OUT_START;
}

int Fader::Init()
{
	brightness = 0;
	fadeSpeed = 0;
	fadeInFlag = false;
	fadeOutFlag = false;
	return 0;
}

FADE_STATE Fader::GetFadeState()
{
	return fadeState;
}

void Fader::Draw()
{
	if (fadeState == FADE_IN_START)
	{
		DrawFormatString(0, 900, 0xff0000, "���݂�fade��Ԃ�FADE_IN_START");
	}
	else if (fadeState == FADE_IN_END)
	{
		DrawFormatString(0, 900, 0xff0000, "���݂�fade��Ԃ�FADE_IN_END");
	}
	else if (fadeState == FADE_OUT_START)
	{
		DrawFormatString(0, 900, 0xff0000, "���݂�fade��Ԃ�FADE_OUT_START");
	}
	else if (fadeState == FADE_OUT_END)
	{
		DrawFormatString(0, 900, 0xff0000, "���݂�fade��Ԃ�FADE_OUT_END");
	}

	DrawFormatString(0, 920, 0xff0000, "�P�x = %d", brightness);
}
