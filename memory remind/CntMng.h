#pragma once
#include "Game_ctr.h"

#define lpCntMng CntMng::GetInstance()

class CntMng
{
public:
	static CntMng &GetInstance(void)											// 静的なｼﾝｸﾞﾙﾄﾝ
	{
		static CntMng s_instance;
		return s_instance;
	}
	void SetCnt(int count);
	int & GetCnt(void);
	void SetEditFlag(bool flag);
	bool & GetEditFlag();

	void GoalSetCnt(int gcount, P_TYPE pType);
	int GoalGetCnt(void);
	int GoalGetCnt2(void);

private:
	CntMng();
	~CntMng();
	int cnt;
	bool editFlag;

	int Gcount[4];		// ゴールした回数
};

