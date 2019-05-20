#pragma once

#define lpFader Fader::GetInstance()

enum FADE_STATE
{
	FADE_IN_START,		//�t�F�[�h�C���J�n
	FADE_IN_END,		//�t�F�[�h�C���I��
	FADE_OUT_START,		//�t�F�[�h�A�E�g�J�n
	FADE_OUT_END,		//�t�F�[�h�A�E�g�I��
	FADE_WAIT			//�ҋ@(�p�r�Ȃ�)
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
	void SetFadeIn(int fadeSpeed);	//�t�F�[�h�C���Z�b�g
	void SetFadeOut(int fadeSpeed);	//�t�F�[�h�A�E�g�Z�b�g
	int Init();
	FADE_STATE GetFadeState();
	Fader();
	~Fader();

private:
	FADE_STATE fadeState;	//�t�F�[�h�̏�ԊǗ�

	int brightness;		//�P�x
	int fadeSpeed;		//�t�F�[�h���鑬��
	bool fadeInFlag;	//�t�F�[�h�C���t���O
	bool fadeOutFlag;	//�t�F�[�h�A�E�g�t���O
};