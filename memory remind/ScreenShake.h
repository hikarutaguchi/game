#pragma once
//��ʗh��N���X

#define lpScreenShaker ScreenShaker::GetInstance()

class ScreenShaker
{
private:
	int _screenH;//���
	float _shakeScale;//�h�ꕝ
	ScreenShaker();
	~ScreenShaker();
public:

	//�h��g���K�[
	void Shake();

	//��ʗh�ꏀ��()
	void PrepareShake();

	//��ʗh��X�V
	void UpdateShake();
	static ScreenShaker &GetInstance(void)											// �ÓI�ȼݸ����
	{
		static ScreenShaker s_instance;
		return s_instance;
	}

};