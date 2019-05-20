#pragma once

#define lpFader Fader::GetInstance()

enum FADE_STATE
{
	FADE_IN_START,		//フェードイン開始
	FADE_IN_END,		//フェードイン終了
	FADE_OUT_START,		//フェードアウト開始
	FADE_OUT_END,		//フェードアウト終了
	FADE_WAIT			//待機(用途なし)
};

class Fader
{
public:
	static Fader &GetInstance(void)
	{
		static Fader s_instance;
		return s_instance;
	}
	void Updata();
	void SetFadeIn(int fadeSpeed);	//フェードインセット
	void SetFadeOut(int fadeSpeed);	//フェードアウトセット
	int Init();
	FADE_STATE GetFadeState();
	Fader();
	~Fader();

private:
	FADE_STATE fadeState;	//フェードの状態管理

	int brightness;		//輝度
	int fadeSpeed;		//フェードする速さ
	bool fadeInFlag;	//フェードインフラグ
	bool fadeOutFlag;	//フェードアウトフラグ
};