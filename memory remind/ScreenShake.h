#pragma once
//‰æ–Ê—h‚êƒNƒ‰ƒX

#define lpScreenShaker ScreenShaker::GetInstance()

class ScreenShaker
{
private:
	int _screenH;//‰æ–Ê
	float _shakeScale;//—h‚ê•
	ScreenShaker();
	~ScreenShaker();
public:

	//—h‚êƒgƒŠƒK[
	void Shake();

	//‰æ–Ê—h‚ê€”õ()
	void PrepareShake();

	//‰æ–Ê—h‚êXV
	void UpdateShake();
	static ScreenShaker &GetInstance(void)											// Ã“I‚È¼İ¸ŞÙÄİ
	{
		static ScreenShaker s_instance;
		return s_instance;
	}

};