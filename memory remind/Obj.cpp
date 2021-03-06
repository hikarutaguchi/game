#include "DxLib.h"
#include "ImageMng.h"
#include "Obj.h"
#include "SelectCur.h"

Obj::Obj()
{
	dir  = DIR_DOWN;
	dir2 = DIR_DOWN;
	visible = true;
}

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)
{
	dir  = DIR_DOWN;
	dir2 = DIR_DOWN;
	visible = true;
}

bool Obj::Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	if (lpSelCur.GetCharFlag(CONTROLLER_P1) == true)
	{
		Init(fileName, divSize, divCnt);
		Setpos(pos);
	}
	return false;
}

bool Obj::Init2(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	if (lpSelCur.GetCharFlag(CONTROLLER_P2) == true)
	{
		Init2(fileName, divSize, divCnt);
		Setpos2(pos);
	}
	return false;
}

bool Obj::Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
	lpImageMng.GetID(fileName, divSize, divCnt);
	//自分のﾒﾝﾊﾞに代入する場合はthisﾎﾟｲﾝﾀ
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt  = divCnt;

	return true;
}

bool Obj::Init2(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
	lpImageMng.GetID(fileName, divSize, divCnt);
	//自分のﾒﾝﾊﾞに代入する場合はthisﾎﾟｲﾝﾀ
	imageName2 = fileName;
	this->divSize = divSize;
	this->divCnt2 = divCnt;

	return true;
}


Obj::~Obj()
{

}

void Obj::UpData(weekListObj objList, const Game_ctr &controller)
{
	SetMove(objList, controller);
}


void Obj::Draw(void)
{
	if (lpSelCur.GetCharFlag(CONTROLLER_P1) == true)
	{
		if (imageName.length() == 0)	//読み込まれてなかったらなにもしない
		{
			return;
		}
		unsigned int id = 0;
		if (animTable.find(animName) != animTable.end())
		{
			int count = (animCnt / animTable[animName][ANIM_TBL_INV]);
			if (animTable[animName][ANIM_TBL_LOOP] || count < animTable[animName][ANIM_TBL_FRAME])	//ﾙｰﾌﾟかどうか、総ﾌﾚｰﾑ数より小さいか
			{
				count = count % animTable[animName][ANIM_TBL_FRAME];
			}
			else    //0,1,2,2,2,2,2が続く処理		ワンショット
			{
				count = animTable[animName][ANIM_TBL_FRAME] - 1;
				animEndFlag = true;
				visible = false;	//　ｱﾆﾒｰｼｮﾝの終わりに消す
			}
			//((animCnt / animTable[animName][ANIM_TBL_INV]) % animTable[animName][ANIM_TBL_FRAME])
			id = animTable[animName][ANIM_TBL_START_ID] + (int)dir
				+ count * divCnt.x;	//そこから何コマ目かどうか
		}
		animCnt++;
		if (visible)
		{
			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
		}
	}
}

void Obj::Draw2(void)
{
	if (lpSelCur.GetCharFlag(CONTROLLER_P2) == true)
	{
		if (imageName2.length() == 0)	//読み込まれてなかったらなにもしない
		{
			return;
		}
		unsigned int id = 0;
		if (animTable.find(animName) != animTable.end())
		{
			int count = (animCnt2 / animTable[animName][ANIM_TBL_INV]);
			if (animTable[animName][ANIM_TBL_LOOP] || count < animTable[animName][ANIM_TBL_FRAME])	//ﾙｰﾌﾟかどうか、総ﾌﾚｰﾑ数より小さいか
			{
				count = count % animTable[animName][ANIM_TBL_FRAME];
			}
			else    //0,1,2,2,2,2,2が続く処理		ワンショット
			{
				count = animTable[animName][ANIM_TBL_FRAME] - 1;
				animEndFlag = true;
				visible = false;	//　ｱﾆﾒｰｼｮﾝの終わりに消す
			}
			//((animCnt / animTable[animName][ANIM_TBL_INV]) % animTable[animName][ANIM_TBL_FRAME])
			id = animTable[animName][ANIM_TBL_START_ID] + (int)dir2
				+ count * divCnt2.x;	//そこから何コマ目かどうか
		}
		animCnt2++;
		if (visible)
		{
			DrawGraph(drawOffset.x + pos2.x, drawOffset.y + pos2.y, IMAGE_ID(imageName2)[id], true);
		}
	}
	//if (imageName2.length() == 0)	//読み込まれてなかったらなにもしない
	//{
	//	return;
	//}
	//unsigned int id2 = 0;
	//if (animTable2.find(animName2) != animTable2.end())
	//{
	//	int count2 = (animCnt2 / animTable2[animName2][ANIM_TBL_INV]);
	//	if (animTable2[animName2][ANIM_TBL_LOOP] || count2 < animTable2[animName2][ANIM_TBL_FRAME])	//ﾙｰﾌﾟかどうか、総ﾌﾚｰﾑ数より小さいか
	//	{
	//		count2 = count2 % animTable2[animName2][ANIM_TBL_FRAME];
	//	}
	//	else    //0,1,2,2,2,2,2が続く処理		ワンショット
	//	{
	//		count2 = animTable2[animName2][ANIM_TBL_FRAME] - 1;
	//		animEndFlag = true;
	//		visible = false;	//　ｱﾆﾒｰｼｮﾝの終わりに消す
	//	}
	//	//((animCnt / animTable[animName][ANIM_TBL_INV]) % animTable[animName][ANIM_TBL_FRAME])
	//	id2 = animTable2[animName2][ANIM_TBL_START_ID] + (int)dir2
	//		+ count2 * divCnt.x;	//そこから何コマ目かどうか
	//}
	//animCnt2++;
	//if (visible)
	//{
	//	DrawGraph(drawOffset.x + pos2.x, drawOffset.y + pos2.y, IMAGE_ID(imageName2)[id2], true);
	//}
}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		if (visible)
		{
			//受けっとたdrawOffsetで表示をずらしておく
			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
			
		}
	}

	if (id < IMAGE_ID(imageName2).size())
	{
		if (visible)
		{
			//受けっとたdrawOffsetで表示をずらしておく
			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName2)[id], true);

		}
	}
}

const VECTOR2 & Obj::GetPos(void)
{
	return pos;
}
//ｷｰはstring型のanimName
bool Obj::AddAnim(std::string animName, int id_x, int id_y, int frame, int inv, bool loop)
{
	animTable[animName][ANIM_TBL_START_ID] = (id_y * divCnt.x) + id_x;
	animTable[animName][ANIM_TBL_FRAME]	   = frame;
	animTable[animName][ANIM_TBL_INV]	   = inv;
	animTable[animName][ANIM_TBL_LOOP]	   = loop;

	return true;
}

bool Obj::SetAnim(std::string animName)
{
	if (Obj::animName == animName)
	{
		return true;
	}
	if (animTable.find(animName) == animTable.end())
	{
		return false;
	}
	Obj::animName = animName;
	Obj::animCnt = 0;
	animEndFlag = false;

	return true;
}

std::string Obj::GetAnim(void)
{
	return animName;
}

void Obj::Setpos(VECTOR2 pos)
{
	Obj::pos  = pos;
}

void Obj::Setpos2(VECTOR2 pos2)
{
	Obj::pos2 = pos2;
}
