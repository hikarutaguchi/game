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
	//array‚ðŽg‚Á‚Ä‚¢‚é‚Ì‚Åµ°ÊÞ°Û°ÄÞ‚É‚È‚é
	dataOld = data;
	GetHitKeyStateAll(&data[0]);
	for (int i = 0; i < GetJoypadNum(); i++)
	{	
		for (int j = 0; j < 28; j++)
		{
			Pad[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
		}
	}
	return true;
}



const KEY_ARRAY & Game_ctr::GetCtr(KEY_TYPE type) const
{
	if (type == KEY_TYPE_OLD)
	{
		return dataOld;
	}
	//ŽQÆ‚È‚Ì‚Å‚»‚Ì‚Ü‚Ü•Ô‚·
	return data;
}

const int & Game_ctr::Get_CTL(KEY_TYPE) const
{
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		return Pad[i];
	}
}
