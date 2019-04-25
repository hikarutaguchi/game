#include "DxLib.h"
#include "Bomb.h"
#include "MapCtl.h"
#include "Game_ctr.h"
#include "classObj.h"

Bomb::Bomb(VECTOR2 setupPos, unsigned int length, VECTOR2 drawOffset) :Obj(drawOffset),
	dirPos {
		VECTOR2{ -1,  0 },	//��
		VECTOR2{  1,  0 },	//�E
		VECTOR2{  0, -1 },	//��
		VECTOR2{  0,  1 }	//��
			}

{

	Init("image/bomb.png", VECTOR2(40 / 2,  140 / 7), VECTOR2(2, 7), setupPos);
	InitAnim();
	SetAnim("�ʏ�");
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
	if (GetAnim() == "�ʏ�")
	{
		//�O�����Z�qreturn ((count) > 0 ? false:true);
		if (lpMapCtl.GetFireMapData(pos))
		{
			count = -1;			
		}
		if (count < 0)
		{
			SetAnim("����");
			//���̾�ā@setfiremapData���Ă�
			//for���ŉ񂵂���
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
		if (fireLength[static_cast<unsigned int>(FIRE_LENGTH::NOW)] >= fireLength[static_cast<unsigned int>(FIRE_LENGTH::LIM)])			// �����L�т�����
		{
			SetAnim("���ő҂�");
		}
		else
		{
			fireLength[static_cast<unsigned int>(FIRE_LENGTH::NOW)] ++;
			//�����ް��̏�������
			//�͈�for���łS����������L�΂��A�����̔��e�̍��W�̂��ꂼ��̕����i�擪�̂݁j���ް�����������ł���
			auto chipSize = lpMapCtl.GetChipSize();			
			auto data	  = lpMapCtl.GetFireMapData(pos);
			for (auto fire_dir : FIRE_DIR())
			{
				if (data & (0xff << (static_cast<unsigned int>(fire_dir) * 8)) )		//data�Ɣ�r����0xff�̒l���V�t�g���Ă�����A1�������Ă����炻���͕ی삳���
				{
					// ����
					if (fireDirFlag[static_cast<unsigned int>(fire_dir)])
					{
						fireDirFlag[static_cast<unsigned int>(fire_dir)] = 
						lpMapCtl.SetFireMapData((pos + dirPos[static_cast<unsigned int>(fire_dir)]	//�ǂ̕���
						* fireLength[static_cast<unsigned int>(FIRE_LENGTH::NOW)] * chipSize), fire_dir);
								//����												�@�傫��
					}
				}
			}
		}
	}
}

bool Bomb::InitAnim(void)
{
	AddAnim("�ʏ�",		0, 0, 2, 6, true );
	AddAnim("����",		1, 0, 7, 3, false);
	AddAnim("���ő҂�", 0, 2, 1, 1, false);
	return true;
}

bool Bomb::CheckDeth(void)
{
	if (GetAnim() == "���ő҂�")
	{
		return animEndFlag;
	}
	return false;
}

bool Bomb::CheckObjType(OBJ_TYPE type)
{
	//�������Ƃ���񂪓����Ȃ�^����������U
	return (type == OBJ_BOMB);
}
