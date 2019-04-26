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
	int Pad[4];
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		Pad[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
		for (int j = 0; j < 28; j++)
		{
			if (Pad[i] & (1 << j))
			{
				VECTOR2 tmpPos(pos);
				//tmpPos�ŋ�ړ�

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
			}
		}
	}
		//int Pad1;
		//Pad1 = GetJoypadInputState(DX_INPUT_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
		//for (int i = 0; i < 28; i++)
		//{      //�{�^��28�����[�v
		//	if (Pad1 & (1 << i)) 
		//	{             //�{�^��i�̓��̓t���O�������Ă�����
		//		DrawFormatString(0, i * 15, GetColor(200, 255, 255), "%d�̃L�[��������Ă��܂�", i);
		//	}
		//}
		//int Pad2;
		//Pad2 = GetJoypadInputState(DX_INPUT_PAD2);        //���͏�Ԃ�Pad�Ɋi�[
		//for (int i = 0; i < 28; i++)
		//{      //�{�^��28�����[�v
		//	if (Pad2 & (1 << i))
		//	{             //�{�^��i�̓��̓t���O�������Ă�����
		//		DrawFormatString(0, i * 15, GetColor(200, 255, 255), "%d�̃L�[��������Ă��܂�", i);
		//	}
		//}
}

bool EditCursor::CheckObjType(OBJ_TYPE type)
{
	//�������Ƃ���񂪓����Ȃ�^����������U
	return (type == OBJ_EDIT_CUR);
}
