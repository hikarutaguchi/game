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
				//最小値からbrightness分プラス
				SetDrawBright(brightness, brightness, brightness);
			}
			else
			{
				//最大値をセットして次に移行
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
				//最大値からbrightness分マイナス
				SetDrawBright(255 - brightness, 255 - brightness, 255 - brightness);
			}
			else
			{
				//最小値をセットして次に移行
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
		DrawFormatString(0, 900, 0xff0000, "現在のfade状態はFADE_IN_START");
	}
	else if (fadeState == FADE_IN_END)
	{
		DrawFormatString(0, 900, 0xff0000, "現在のfade状態はFADE_IN_END");
	}
	else if (fadeState == FADE_OUT_START)
	{
		DrawFormatString(0, 900, 0xff0000, "現在のfade状態はFADE_OUT_START");
	}
	else if (fadeState == FADE_OUT_END)
	{
		DrawFormatString(0, 900, 0xff0000, "現在のfade状態はFADE_OUT_END");
	}

	DrawFormatString(0, 920, 0xff0000, "輝度 = %d", brightness);
}
