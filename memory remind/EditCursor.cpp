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
	id = static_cast<MAP_ID>(MAP_ID::WALL1);
	//���øï�ނ̏ꍇ
	//Obj::drawOffset = drawOffset;
}

EditCursor::EditCursor()
{
	keyGetRng = EDIT_KEY_GET_DEF_RNG;
	inputFram = EDIT_KEY_GET_DEF_RNG;
	id = static_cast<MAP_ID>(MAP_ID::WALL1);
}


EditCursor::~EditCursor()
{

}

void EditCursor::Draw(void)
{
	//��̧�����ިݸ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//���̏���BLEND�����Č��ɖ߂��̂�Y��Ă������̂��߂̶ް�ޏ���
	Obj::Draw((int)id);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs( (int)(animCnt % 512) - 256));
	Obj::Draw((static_cast<int>(MAP_ID::CUR)));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	animCnt += 10;
}

void EditCursor::SetMove(weekListObj objList,const Game_ctr &controller)
{
		GetJoypadNum();
	int Pad1;
	Pad1 = GetJoypadInputState(DX_INPUT_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
	for (int i = 0; i < 28; i++)
	{      //�{�^��28�����[�v
		if (Pad1 & (1 << i)) 
		{             //�{�^��i�̓��̓t���O�������Ă�����
			DrawFormatString(0, i * 15, GetColor(200, 255, 255), "%d�̃L�[��������Ă��܂�", i);
		}
	}
	int Pad2;
	Pad2 = GetJoypadInputState(DX_INPUT_PAD2);        //���͏�Ԃ�Pad�Ɋi�[
	for (int i = 0; i < 28; i++)
	{      //�{�^��28�����[�v
		if (Pad2 & (1 << i))
		{             //�{�^��i�̓��̓t���O�������Ă�����
			DrawFormatString(0, i * 15, GetColor(200, 255, 255), "%d�̃L�[��������Ă��܂�", i);
		}
	}
	//auto cnt = controller.GetCtr(); ����ł�OK
	KEY_ARRAY cnt	 = controller.GetCtr(KEY_TYPE_NOW);
	KEY_ARRAY cntOld = controller.GetCtr(KEY_TYPE_OLD);
	VECTOR2 tmpPos(pos);
	//tmpPos�ŋ�ړ�
	if (PAD_INPUT_LEFT & Pad1)
	{
		if (tmpPos.x > 0)
		{
			tmpPos.x -= divSize.x;
		}
	}
	if (PAD_INPUT_RIGHT & Pad1)
	{
		if (tmpPos.x < lpScene.GetInstance().GetGameSize().x - divSize.x)
		{
			tmpPos.x += divSize.x;
		}
	}
	if (PAD_INPUT_DOWN & Pad1)
	{
		if (tmpPos.y < lpScene.GetInstance().GetGameSize().y - divSize.y)
		{
			tmpPos.y += divSize.y;
		}
	}
	if (PAD_INPUT_UP & Pad1)
	{
		if (tmpPos.y > 0)
		{
			tmpPos.y -= divSize.y;
		}
	}

	if (tmpPos != pos)	//������緰���͂�����
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
	if ((cnt[KEY_INPUT_X]) && (!cntOld[KEY_INPUT_X]))
	{
		// id = (MAP_ID) (id + 1 >= MAP_ID_MAX ? MAP_ID_NON:id + 1) �O�����Z�q�ŏ������ꍇ
		id = (MAP_ID)(id + 1);
		if (id > MAP_ID::ITEM_SPEED)
		{
			id = MAP_ID::BOMB;
		}
	}
	if ((cnt[KEY_INPUT_Z]) && (!cntOld[KEY_INPUT_Z]))
	{
		id = (MAP_ID)(id - 1);
		if (id < MAP_ID::BOMB)
		{
			id = MAP_ID::ITEM_SPEED;
		}
	}
	if ((cnt[KEY_INPUT_SPACE]))/* && (!cntOld[KEY_INPUT_SPACE]))*/
	{
		lpMapCtl.SetMapData(pos, id);
	}
	if ((cnt[KEY_INPUT_F]) && (!cntOld[KEY_INPUT_F]))
	{
		for (int j = 0; j < 2; j++)
		{
			lpMapCtl.SetMapData(pos, id);
			pos.x += divSize.x;
		}
	}
	if ((cnt[KEY_INPUT_0]))
	{
		lpMapCtl.SetMapData(pos, MAP_ID::NON);
	}
	if ((cnt[KEY_INPUT_H]) && (!cntOld[KEY_INPUT_H]))
	{
		for (int j = 0; j < 2; j++)
		{
			lpMapCtl.SetMapData(pos, id);
			pos.x -= divSize.x;
		}
	}
}

bool EditCursor::CheckObjType(OBJ_TYPE type)
{
	//�������Ƃ���񂪓����Ȃ�^����������U
	return (type == OBJ_EDIT_CUR);
}
