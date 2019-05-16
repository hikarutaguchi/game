#include "CntMng.h"



void CntMng::SetCnt(int count)
{
	cnt += count;
}

int & CntMng::GetCnt(void)
{
	return cnt;
}

CntMng::CntMng()
{
}


CntMng::~CntMng()
{
}
