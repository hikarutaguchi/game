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
	//array‚ğg‚Á‚Ä‚¢‚é‚Ì‚Åµ°ÊŞ°Û°ÄŞ‚É‚È‚é
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
	//QÆ‚È‚Ì‚Å‚»‚Ì‚Ü‚Ü•Ô‚·
	return data;
}
