#include "DxLib.h"
#include "EditCursor.h"
#include "SceneMng.h"
#include "Game_ctr.h"

#define EDIT_KEY_GET_DEF_RNG 30
#define MIN_KEY_RNG 5

#define lpScene SceneMng::GetInstance()

EditCursor::EditCursor(VECTOR2 drawOffset) :Obj(drawOffset)
{
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFram = EDIT_KEY_GET_DEF_RNG;
	id = static_cast<MAP_ID>(MAP_ID::IWA);
	//ÌßÛÃ¸Ã¯ÄŞ‚Ìê‡
	//Obj::drawOffset = drawOffset;
}

EditCursor::EditCursor()
{
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFram = EDIT_KEY_GET_DEF_RNG;
	id = static_cast<MAP_ID>(MAP_ID::IWA);
}


EditCursor::~EditCursor()
{

}

void EditCursor::Draw(void)
{
	//±ÙÌ§ÌŞÚİÃŞ¨İ¸Ş
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//‘¼‚ÌŠ‚ÅBLEND‚ğ‚µ‚ÄŒ³‚É–ß‚·‚Ì‚ğ–Y‚ê‚Ä‚¢‚½‚Ì‚½‚ß‚Ì¶Ş°ÄŞˆ—
	Obj::Draw((int)id);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((int)(animCnt % 512) - 256));
	Obj::Draw((static_cast<int>(MAP_ID::YUKA)));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	animCnt += 10;
}

void EditCursor::SetMove(weekListObj objList, const Game_ctr &controller)
{
	//auto cnt = controller.GetCtr(KEY_TYPE_NOW);
	//auto cntOld = controller.GetCtr(KEY_TYPE_OLD);

	int Pad[4];
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		Pad[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
		for (int j = 0; j < 28; j++)
		{
			if (Pad[i] & (1 << j))
			{
				VECTOR2 tmpPos(pos);
				//tmpPos‚Å‹óˆÚ“®

				if (PAD_INPUT_LEFT & Pad[i])
				{
					if (tmpPos.x > 0)
					{
						tmpPos.x -= divSize.x;
					}
				}
				if (PAD_INPUT_RIGHT & Pad[i])
				{
					if (tmpPos.x < lpScene.GetInstance().GetGameSize().x - divSize.x)
					{
						tmpPos.x += divSize.x;
					}
				}
				if (PAD_INPUT_DOWN & Pad[i])
				{
					if (tmpPos.y < lpScene.GetInstance().GetGameSize().y - divSize.y)
					{
						tmpPos.y += divSize.y;
					}
				}
				if (PAD_INPUT_UP & Pad[i])
				{
					if (tmpPos.y > 0)
					{
						tmpPos.y -= divSize.y;
					}
				}

				if ((PAD_INPUT_B & Pad[i]) && (count > 15))
				{
					id = (MAP_ID)(id + 1);
					if (id > MAP_ID::TOOL)
					{
						id = MAP_ID::YUKA + 1;
					}
					count = 0;
				}

				if (tmpPos != pos)	//ˆá‚Á‚½‚ç·°“ü—Í‚ª‚ ‚é
				{
					inputFram++;
					if (inputFram >= keyGetRng)
					{
						pos = tmpPos;
						inputFram = 0;
						keyGetRng /= 2;
						if (keyGetRng < MIN_KEY_RNG)
						{
							keyGetRng = MIN_KEY_RNG;
						}
					}
				}
				else
				{
					keyGetRng = EDIT_KEY_GET_DEF_RNG;
					inputFram = EDIT_KEY_GET_DEF_RNG;
				}
			}
		}
		if (PAD_INPUT_4 & Pad[i] && count > 30)
		{
			lpMapCtl.SetMapData(pos, id);
			count = 0;
		}
	}
	//if ((cnt[KEY_INPUT_X]) && (!cntOld[KEY_INPUT_X]))
	//{
	//	// id = (MAP_ID) (id + 1 >= MAP_ID_MAX ? MAP_ID_NON:id + 1) O€‰‰Zq‚Å‘‚¢‚½ê‡
	//	id = (MAP_ID)(id + 1);
	//	if (id > MAP_ID::TOOL)
	//	{
	//		id = MAP_ID::YUKA + 1;
	//	}
	//}
	count++;
	//if (cnt[KEY_INPUT_SPACE] & (~cntOld[KEY_INPUT_SPACE]))
	//{
	//	lpMapCtl.SetMapData(pos, id);
	//}
}

bool EditCursor::CheckObjType(OBJ_TYPE type)
{
	//‚¤‚¯‚Á‚Æ‚½î•ñ‚ª“¯‚¶‚È‚ç^‚¿‚ª‚Á‚½‚ç‹U
	return (type == OBJ_EDIT_CUR);
}
