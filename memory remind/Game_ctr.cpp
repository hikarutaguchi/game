#include "DxLib.h"
#include "Game_ctr.h"



Game_ctr::Game_ctr()
{

}


Game_ctr::~Game_ctr()
{

}

bool Game_ctr::Updata(void)
{
	//array���g���Ă���̂ŵ��ް۰�ނɂȂ�
	dataOld = data;
	GetHitKeyStateAll(&data[0]);
	return true;
}



const KEY_ARRAY & Game_ctr::GetCtr(KEY_TYPE type) const
{
	if (type == KEY_TYPE_OLD)
	{
		return dataOld;
	}
	//�Q�ƂȂ̂ł��̂܂ܕԂ�
	return data;
}
