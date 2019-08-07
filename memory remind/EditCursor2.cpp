#include "DxLib.h"
#include "EditCursor2.h"
#include "SceneMng.h"
#include "CntMng.h"
#include "TitleScene.h"

#define EDIT_KEY_GET_DEF_RNG 30
#define MIN_KEY_RNG 5

#define lpScene SceneMng::GetInstance()

EditCursor2::EditCursor2(VECTOR2 drawOffset, int pad) :Obj(drawOffset)
{
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFram = EDIT_KEY_GET_DEF_RNG;
	id = static_cast<MAP_ID>(MAP_ID::HOLE);
	itemButton = PAD_MAX;
	setButton = PAD_MAX;
	count = 0;
	pos.y += 64;
	//Ãﬂ€√∏√ØƒﬁÇÃèÍçá
	//Obj::drawOffset = drawOffset;
}

EditCursor2::EditCursor2()
{
	lpCntMng.SetEditFlag(false, CONTROLLER_P2);
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFram = EDIT_KEY_GET_DEF_RNG;
	itemButton = PAD_MAX;
	setButton = PAD_MAX;
	count = 0;
	id = static_cast<MAP_ID>(MAP_ID::HOLE);
}


EditCursor2::~EditCursor2()
{

}

void EditCursor2::Draw(void)
{
	//±ŸÃßÃﬁ⁄›√ﬁ®›∏ﬁ
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ëºÇÃèäÇ≈BLENDÇÇµÇƒå≥Ç…ñﬂÇ∑ÇÃÇñYÇÍÇƒÇ¢ÇΩéûÇÃÇΩÇﬂÇÃ∂ﬁ∞ƒﬁèàóù
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((int)(animCnt % 512) - 256));
	Obj::Draw((int)id);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	animCnt += 10;
}

void EditCursor2::SetMove(weekListObj objList, const Game_ctr &controller)
{
	int Pad2;
	Pad2 = GetJoypadInputState(DX_INPUT_PAD2);

	for (int j = 0; j < 28; j++)
	{
		if (Pad2 & (1 << j))
		{
			VECTOR2 tmpPos(pos);
			//tmpPosÇ≈ãÛà⁄ìÆ

			if (PAD_INPUT_LEFT & Pad2)
			{
				if (tmpPos.x > 0)
				{
					tmpPos.x -= divSize.x;
				}
			}
			if (PAD_INPUT_RIGHT & Pad2)
			{
				if (tmpPos.x < lpSceneMng.GetGameSize().x - divSize.x)
				{
					tmpPos.x += divSize.x;
				}
			}
			if (PAD_INPUT_DOWN & Pad2)
			{
				if (tmpPos.y < lpSceneMng.GetGameSize().y - divSize.y)
				{
					tmpPos.y += divSize.y;
				}
			}
			if (PAD_INPUT_UP & Pad2)
			{
				if (tmpPos.y > 0)
				{
					tmpPos.y -= divSize.y;
				}
			}

			if (tmpPos != pos)	//à·Ç¡ÇΩÇÁ∑∞ì¸óÕÇ™Ç†ÇÈ
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

	if (itemButton == PAD_FREE)
	{
		if (controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P2) == PAD_PUSH)
		{
			PlaySoundMem(choice, DX_PLAYTYPE_BACK);
			if (lpSelCur.GetCharData(CONTROLLER_P2) == 1)
			{
				id = (MAP_ID)(id + 1);
				if (id > MAP_ID::NULLL)
				{
					id = MAP_ID::HOLE;
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P2) == 2 && id == MAP_ID::HOLE)
			{
				id = (MAP_ID)(id + 4);
			}
			else if (lpSelCur.GetCharData(CONTROLLER_P2) == 2 && id != MAP_ID::HOLE)
			{
				id = (MAP_ID)(id + 1);

				if (id > MAP_ID::MAGIC1)
				{
					id = MAP_ID::HOLE;
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P2) == 3 && id == MAP_ID::HOLE)
			{
				id = (MAP_ID)(id + 7);
			}
			else if (lpSelCur.GetCharData(CONTROLLER_P2) == 3 && id != MAP_ID::HOLE)
			{
				id = (MAP_ID)(id + 1);

				if (id > MAP_ID::TOOL)
				{
					id = MAP_ID::HOLE;
				}
			}
		}
	}

	if (setButton == PAD_FREE)
	{
		if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P2) == PAD_PUSH)
		{
			if (pos.x > 128 && pos.x < 768)
			{
				if (count < 2)
				{
					switch (count)
					{
					case 0:
						lpMapCtl.SetMapData(pos, id);
						befo2pos = pos;
						befo2ID = id;
						if (lpMapCtl.SetMapData(pos, id) != false)
						{
							count += 1;
						}
						PlaySoundMem(kettei, DX_PLAYTYPE_BACK);
						break;
					case 1:
						lpMapCtl.SetMapData(pos, id);
						beforepos = pos;
						beforeID = id;
						if (lpMapCtl.SetMapData(pos, id) != false)
						{
							count += 1;
							lpCntMng.SetEditFlag(true, CONTROLLER_P2);
						}
						PlaySoundMem(kettei, DX_PLAYTYPE_BACK);
						break;
					default:
						break;
					}
				}
				else
				{
					if (CheckSoundMem(bu_bu) == 0)
					{
						PlaySoundMem(bu_bu, DX_PLAYTYPE_BACK);
					}
				}
			}
		}
	}

	if (resetButton == PAD_FREE)
	{
		if (controller.GetCtr(INPUT_BUTTON_X, CONTROLLER_P2) == PAD_PUSH)
		{
			lpCntMng.SetEditFlag(false, CONTROLLER_P2);
			switch (count)
			{
			case 1:
				pos = befo2pos;
				lpMapCtl.SetMapData(befo2pos, MAP_ID::YUKA);
				count -= 1;
				PlaySoundMem(cansell, DX_PLAYTYPE_BACK);
				break;
			case 2:
				pos = beforepos;
				lpMapCtl.SetMapData(beforepos, MAP_ID::YUKA);
				count -= 1;
				PlaySoundMem(cansell, DX_PLAYTYPE_BACK);
				break;
			default:
				break;
			}
		}
	}

	itemButton = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P2);
	setButton = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P2);
	resetButton = controller.GetCtr(INPUT_BUTTON_X, CONTROLLER_P2);

	lpMapCtl.GetMapID(pos, id);

}

bool EditCursor2::CheckObjType(OBJ_TYPE type)
{
	//Ç§ÇØÇ¡Ç∆ÇΩèÓïÒÇ™ìØÇ∂Ç»ÇÁê^ÇøÇ™Ç¡ÇΩÇÁãU
	return (type == OBJ_EDIT_CUR);
}