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
	//�Q�ƂȂ̂ł��̂܂ܕԂ�
	return data;
}

const int & Game_ctr::Get_CTL(KEY_TYPE) const
{
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		return Pad[i];
	}
}
