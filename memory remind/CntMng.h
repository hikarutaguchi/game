#pragma once
#include "Game_ctr.h"

#define lpCntMng CntMng::GetInstance()

class CntMng
{
public:
	static CntMng &GetInstance(void)											// ê√ìIÇ»º›∏ﬁŸƒ›
	{
		static CntMng s_instance;
		return s_instance;
	}
	void SetCnt(int count);
	int & GetCnt(void);
	void SetEditFlag(bool flag, P_TYPE ptype);
	bool & GetEditFlag(P_TYPE ptype);

	void SetGoalFlag(bool flag, P_TYPE ptype);
	bool & GetGoalFlag(P_TYPE ptype);

	void GoalSetCnt(int gcount, P_TYPE pType);
	int GoalGetCnt(void);
	int GoalGetCnt2(void);

private:
	CntMng();
	~CntMng();
	int cnt;
	bool editFlag[CONTROLLER_MAX];

	bool GoalFlag[CONTROLLER_MAX];

	int Gcount[4];		// ÉSÅ[ÉãÇµÇΩâÒêî
};

