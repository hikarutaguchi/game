#include "CntMng.h"



void CntMng::SetCnt(int count)
{
	cnt += count;
}

int & CntMng::GetCnt(void)
{
	return cnt;
}

void CntMng::SetEditFlag(bool flag)
{
	editFlag = flag;
}

bool & CntMng::GetEditFlag()
{
	return editFlag;
}

CntMng::CntMng()
{
	editFlag = false;
}


CntMng::~CntMng()
{
}
