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
	case FADE_IN_STARE:
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
				SetDrawBright(255, 255, 255);
				brightness = 0;
				fadeState = FADE_IN_END;
			}
		}
		break;
	case FADE_IN_END:
		fadeInFlag = false;
		break;
	case FADE_OUT_STARE:
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
	fadeState = FADE_IN_STARE;
}

void Fader::SetFadeOut(int fadeSpeed)
{
	this->fadeSpeed = fadeSpeed;
	fadeOutFlag = true;
	fadeState = FADE_OUT_STARE;
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
