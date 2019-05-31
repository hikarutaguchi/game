#include "CntMng.h"



void CntMng::SetCnt(int count)
{
	cnt += count;
}

int & CntMng::GetCnt(void)
{
	return cnt;
}

void CntMng::SetEditFlag(bool flag,P_TYPE ptype)
{
	editFlag[ptype] = flag;
}

bool & CntMng::GetEditFlag(P_TYPE ptype)
{
	return editFlag[ptype];
}

void CntMng::GoalSetCnt(int gcount, P_TYPE pType)
{
	switch (pType)
	{
	case CONTROLLER_P1:
		Gcount[0] = gcount;
		break;
	case CONTROLLER_P2:
		Gcount[1] = gcount;
		break;
	}
}

int CntMng::GoalGetCnt(void)
{
	return Gcount[0];
}

int CntMng::GoalGetCnt2(void)
{
	return Gcount[1];
}

CntMng::CntMng()
{
}


CntMng::~CntMng()
{
}
