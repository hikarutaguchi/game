#pragma once
#define lpCntMng CntMng::GetInstance()

class CntMng
{
public:
	static CntMng &GetInstance(void)											// �ÓI�ȼݸ����
	{
		static CntMng s_instance;
		return s_instance;
	}
	void SetCnt(int count);
	int & GetCnt(void);
	void SetEditFlag(bool flag);
	bool & GetEditFlag();
private:
	CntMng();
	~CntMng();
	int cnt;
	bool editFlag;
};

