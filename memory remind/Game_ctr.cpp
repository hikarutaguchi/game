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
	//arrayを使っているのでｵｰﾊﾞｰﾛｰﾄﾞになる
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
	//参照なのでそのまま返す
	return data;
}
