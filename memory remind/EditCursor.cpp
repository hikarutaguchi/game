#include "DxLib.h"
#include "EditCursor.h"
#include "SceneMng.h"
#include "Game_ctr.h"
#include "SelectCur.h"

#define EDIT_KEY_GET_DEF_RNG 30
#define MIN_KEY_RNG 5

EditCursor::EditCursor(VECTOR2 drawOffset, int pad) :Obj(drawOffset)
{
	kettei = LoadSoundMem("sound/allScene/se_kettei.mp3");
	cansell = LoadSoundMem("sound/allScene/se_cansell.mp3");
	choice = LoadSoundMem("sound/allScene/se_choice.mp3");
	bu_bu = LoadSoundMem("sound/allScene/se_modoru.mp3");

	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFram = EDIT_KEY_GET_DEF_RNG;
	id = static_cast<MAP_ID>(MAP_ID::HOLE);
	//Ãﬂ€√∏√ØƒﬁÇÃèÍçá
	//Obj::drawOffset = drawOffset;
}

EditCursor::EditCursor()
{
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFram = EDIT_KEY_GET_DEF_RNG;
	itemButton = PAD_MAX;
	setButton = PAD_MAX;
	count = 0;
	id = static_cast<MAP_ID>(MAP_ID::HOLE);
}


EditCursor::~EditCursor()
{

}

void EditCursor::Draw(void)
{
	//±ŸÃßÃﬁ⁄›√ﬁ®›∏ﬁ
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ëºÇÃèäÇ≈BLENDÇÇµÇƒå≥Ç…ñﬂÇ∑ÇÃÇñYÇÍÇƒÇ¢ÇΩéûÇÃÇΩÇﬂÇÃ∂ﬁ∞ƒﬁèàóù	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((int)(animCnt % 512) - 256));
	Obj::Draw((int)id);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	animCnt += 10;
}

void EditCursor::SetMove(weekListObj objList, const Game_ctr &controller)
{
	//auto cnt = controller.GetCtr(KEY_TYPE_NOW);
	//auto cntOld = controller.GetCtr(KEY_TYPE_OLD);
	int Pad;
	Pad = GetJoypadInputState(DX_INPUT_PAD1);

	for (int j = 0; j < 28; j++)
	{
		if (Pad & (1 << j))
		{
			VECTOR2 tmpPos(pos);
			//tmpPosÇ≈ãÛà⁄ìÆ

			if (PAD_INPUT_LEFT & Pad)
			{
				if (tmpPos.x > 0)
				{
					tmpPos.x -= divSize.x;
				}
			}
			if (PAD_INPUT_RIGHT & Pad)
			{
				if (tmpPos.x < lpSceneMng.GetGameSize().x - divSize.x)
				{
					tmpPos.x += divSize.x;
				}
			}
			if (PAD_INPUT_DOWN & Pad)
			{
				if (tmpPos.y < lpSceneMng.GetInstance().GetGameSize().y - divSize.y)
				{
					tmpPos.y += divSize.y;
				}
			}
			if (PAD_INPUT_UP & Pad)
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
		if (controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P1) == PAD_PUSH)
		{
			/*PlaySoundMem(choice, DX_PLAYTYPE_BACK);
			if (lpSelCur.GetCharData(CONTROLLER_P1) == 1)
			{
				id = (MAP_ID)(id + 1);
				if (id > MAP_ID::NULLL)
				{
					id = MAP_ID::HOLE;
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P1) == 2 && id == MAP_ID::HOLE)
			{
				id = (MAP_ID)(id + 4);
			}
			else if (lpSelCur.GetCharData(CONTROLLER_P1) == 2 && id != MAP_ID::HOLE)
			{
				id = (MAP_ID)(id + 1);

				if (id > MAP_ID::MAGIC1)
				{
					id = MAP_ID::HOLE;
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P1) == 3 && id == MAP_ID::HOLE)
			{
				id = (MAP_ID)(id + 7);
			}
			else if (lpSelCur.GetCharData(CONTROLLER_P1) == 3 && id != MAP_ID::HOLE)
			{
				id = (MAP_ID)(id + 1);

				if (id > MAP_ID::TOOL)
				{
					id = MAP_ID::HOLE;
				}
			}*/
			id = (MAP_ID)(id + 1);
			if (id > MAP_ID::GOAL)
			{
				id = MAP_ID::HOLE;
			}
		}
	}

	if (setButton == PAD_FREE)
	{
		if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P1) == PAD_PUSH)
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

	if (resetButton == PAD_FREE)
	{
		if (controller.GetCtr(INPUT_BUTTON_X, CONTROLLER_P1) == PAD_PUSH)
		{
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

	itemButton = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P1);
	setButton = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P1);
	resetButton = controller.GetCtr(INPUT_BUTTON_X, CONTROLLER_P1);

	lpMapCtl.GetMapID(pos,id);

}

bool EditCursor::CheckObjType(OBJ_TYPE type)
{
	//Ç§ÇØÇ¡Ç∆ÇΩèÓïÒÇ™ìØÇ∂Ç»ÇÁê^ÇøÇ™Ç¡ÇΩÇÁãU
	return (type == OBJ_EDIT_CUR);
}
