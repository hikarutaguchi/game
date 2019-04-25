#include "DxLib.h"
#include "Bomb.h"
#include "MapCtl.h"
#include "Game_ctr.h"
#include "classObj.h"

Bomb::Bomb(VECTOR2 setupPos, unsigned int length, VECTOR2 drawOffset) :Obj(drawOffset),
	dirPos {
		VECTOR2{ -1,  0 },	//左
		VECTOR2{  1,  0 },	//右
		VECTOR2{  0, -1 },	//上
		VECTOR2{  0,  1 }	//下
			}

{

	Init("image/bomb.png", VECTOR2(40 / 2,  140 / 7), VECTOR2(2, 7), setupPos);
	InitAnim();
	SetAnim("通常");
	count = 180;
	fireDirFlag = {true,true,true,true};
	fireLength[static_cast<unsigned int>(FIRE_LENGTH::LIM)] = length;
	fireLength[static_cast<unsigned int>(FIRE_LENGTH::NOW)] = 0;
}


Bomb::~Bomb()
{
}

void Bomb::SetMove(weekListObj objList, const Game_ctr & controller)
{
	if (GetAnim() == "通常")
	{
		//三項演算子return ((count) > 0 ? false:true);
		if (lpMapCtl.GetFireMapData(pos))
		{
			count = -1;			
		}
		if (count < 0)
		{
			SetAnim("爆発");
			//炎のｾｯﾄ　setfiremapDataを呼ぶ
			//for文で回したい
			for (auto dir : FIRE_DIR())
			{
				lpMapCtl.SetFireMapData(pos,dir);
			}
		}
		else
		{
			count--;
		}

	}
	else
	{
		if (fireLength[static_cast<unsigned int>(FIRE_LENGTH::NOW)] >= fireLength[static_cast<unsigned int>(FIRE_LENGTH::LIM)])			// 炎が伸びたあと
		{
			SetAnim("消滅待ち");
		}
		else
		{
			fireLength[static_cast<unsigned int>(FIRE_LENGTH::NOW)] ++;
			//炎のﾃﾞｰﾀの書き込み
			//範囲for分で４方向分炎を伸ばす、自分の爆弾の座標のそれぞれの方向（先頭のみ）にﾃﾞｰﾀを書き込んでいく
			auto chipSize = lpMapCtl.GetChipSize();			
			auto data	  = lpMapCtl.GetFireMapData(pos);
			for (auto fire_dir : FIRE_DIR())
			{
				if (data & (0xff << (static_cast<unsigned int>(fire_dir) * 8)) )		//dataと比較して0xffの値をシフトしてあげる、1が立っていたらそこは保護される
				{
					// 延焼
					if (fireDirFlag[static_cast<unsigned int>(fire_dir)])
					{
						fireDirFlag[static_cast<unsigned int>(fire_dir)] = 
						lpMapCtl.SetFireMapData((pos + dirPos[static_cast<unsigned int>(fire_dir)]	//どの方向
						* fireLength[static_cast<unsigned int>(FIRE_LENGTH::NOW)] * chipSize), fire_dir);
								//長さ												　大きさ
					}
				}
			}
		}
	}
}

bool Bomb::InitAnim(void)
{
	AddAnim("通常",		0, 0, 2, 6, true );
	AddAnim("爆発",		1, 0, 7, 3, false);
	AddAnim("消滅待ち", 0, 2, 1, 1, false);
	return true;
}

bool Bomb::CheckDeth(void)
{
	if (GetAnim() == "消滅待ち")
	{
		return animEndFlag;
	}
	return false;
}

bool Bomb::CheckObjType(OBJ_TYPE type)
{
	//うけっとた情報が同じなら真ちがったら偽
	return (type == OBJ_BOMB);
}
