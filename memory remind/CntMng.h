#pragma once
#define lpCntMng CntMng::GetInstance()

class CntMng
{
public:
	static CntMng &GetInstance(void)											// Ã“I‚È¼İ¸ŞÙÄİ
	{
		static CntMng s_instance;
		return s_instance;
	}
	void SetCnt(int count);
	int & GetCnt(void);
private:
	CntMng();
	~CntMng();
	int cnt;
};

