#pragma once
//ζΚhκNX

#define lpScreenShaker ScreenShaker::GetInstance()

class ScreenShaker
{
private:
	int _screenH;//ζΚ
	float _shakeScale;//hκ
	ScreenShaker();
	~ScreenShaker();
public:

	//hκgK[
	void Shake();

	//ζΚhκυ()
	void PrepareShake();

	//ζΚhκXV
	void UpdateShake();
	static ScreenShaker &GetInstance(void)											// ΓIΘΌέΈήΩΔέ
	{
		static ScreenShaker s_instance;
		return s_instance;
	}

};