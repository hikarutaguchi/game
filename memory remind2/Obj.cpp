#include "DxLib.h"
#include "Obj.h"
#include "ImageMng.h"



Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)	//�������q
{
	dir = DIR_DOWN;
}

Obj::Obj()
{
}

bool Obj::Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
	lpImageMng.GetID(fileName, divSize, divCnt);
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt = divCnt;

	return true;
}

bool Obj::Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	Init(fileName, divSize, divCnt);
	SetPos(pos);
	return true;
}


Obj::~Obj()
{
}

//void Obj::UpDate(const GameCtr &Ctr, weakObjList objList)
//{
//	SetMove(Ctr, objList);
//}

void Obj::Draw(void)
{
	if (imageName.length() == 0)
	{
		return;
	}
	unsigned int id = 0;
	if (animTable.find(animName) != animTable.end())
	{
		int count = (animCnt / animTable[animName][ANIM_TBL_INV]);
		if (animTable[animName][ANIM_TBL_LOOP] || count < animTable[animName][ANIM_TBL_FLAME])//or�����@01�ƃ��[�v����ꍇ
		{
			count = count % animTable[animName][ANIM_TBL_FLAME];
		}
		else
		{
			count = animTable[animName][ANIM_TBL_FLAME] - 1;//2����������
			animEndFlag = true;
		}


		id = (animTable[animName][ANIM_TBL_START_ID]) + (int)dir			//�I�t�Z�b�g
			+ count/*((animCnt/animTable[animName][ANIM_TBL_INV])% animTable[animName][ANIM_TBL_FLAME])*/ * divCnt.x;	//	�A�j���[�V����
	}


	animCnt++;

	if (id < IMAGE_ID(imageName).size())
	{
		DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
	}
}

void Obj::Draw(unsigned int id)
{
	/*if (id < IMAGE_ID(imageName).size())
	{
		DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
	}*/
	return;
}

const VECTOR2 & Obj::GetPos(void)
{
	return pos;
}

bool Obj::AddAnim(std::string animName, int id_x, int id_y, int flame, int inv, bool loop)
{
	animTable[animName][ANIM_TBL_START_ID] = (divCnt.x * id_y) + id_x;
	animTable[animName][ANIM_TBL_FLAME] = flame;
	animTable[animName][ANIM_TBL_INV] = inv;
	animTable[animName][ANIM_TBL_LOOP] = loop;
	return true;
}

bool Obj::SetAnim(std::string animName)
{
	if (Obj::animName == animName)			//���݂��Ă��Ȃ�
	{
		return true;
	}
	if (animTable.find(animName) == animTable.end())	//�d�����Ă���
	{
		return false;
	}
	Obj::animName = animName;
	Obj::animCnt = 0;				//Obj::�̖��O��Ԃ͏����Ȃ��Ă��ǂ�
	animEndFlag = false;
	return true;
}

std::string Obj::GetAnim(void)
{

	return animName;
}

void Obj::SetPos(VECTOR2 pos)
{
	Obj::pos = pos;

}