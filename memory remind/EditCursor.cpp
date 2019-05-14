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
	//Ãﬂ€√∏√ØƒﬁÇÃèÍçá
	//Obj::drawOffset = drawOffset;
}

EditCursor::EditCursor()
{
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFram = EDIT_KEY_GET_DEF_RNG;
	itemButton = PAD_MAX;
	setButton = PAD_MAX;
	id = static_cast<MAP_ID>(MAP_ID::IWA);
}


EditCursor::~EditCursor()
{

}

void EditCursor::Draw(void)
{
	//±ŸÃßÃﬁ⁄›√ﬁ®›∏ﬁ
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ëºÇÃèäÇ≈BLENDÇÇµÇƒå≥Ç…ñﬂÇ∑ÇÃÇñYÇÍÇƒÇ¢ÇΩéûÇÃÇΩÇﬂÇÃ∂ﬁ∞ƒﬁèàóù
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
				//tmpPosÇ≈ãÛà⁄ìÆ

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
		if (PAD_INPUT_4 & Pad[i] && count > 30)
		{
			lpMapCtl.SetMapData(pos, id);
			count = 0;
		}
	}

	if (itemButton == PAD_FREE)
	{
		if (controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_Y) == PAD_PUSH)
		{
			id = (MAP_ID)(id + 1);
			if (id > MAP_ID::TOOL)
			{
				id = MAP_ID::YUKA + 1;
			}
		}
	}

	if (setButton == PAD_FREE)
	{
		if (controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_B) == PAD_PUSH)
		{
			lpMapCtl.SetMapData(pos, id);
		}
	}


	itemButton = controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_Y);
	setButton  = controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_B);

}

bool EditCursor::CheckObjType(OBJ_TYPE type)
{
	//Ç§ÇØÇ¡Ç∆ÇΩèÓïÒÇ™ìØÇ∂Ç»ÇÁê^ÇøÇ™Ç¡ÇΩÇÁãU
	return (type == OBJ_EDIT_CUR);
}
