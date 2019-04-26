#include "DxLib.h"
#include "ImageMng.h"
#include "Obj.h"

Obj::Obj()
{
	dir = DIR_DOWN;
	visible = true;
}

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)
{
	dir = DIR_DOWN;
	visible = true;
}

bool Obj::Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	Init(fileName, divSize, divCnt);
	Setpos(pos);
	return false;
}

bool Obj::Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
	lpImageMng.GetID(fileName, divSize, divCnt);
	//���������ނɑ������ꍇ��this�߲��
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt  = divCnt;

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
	if (imageName.length() == 0)	//�ǂݍ��܂�ĂȂ�������Ȃɂ����Ȃ�
	{
		return;
	}
	unsigned int id = 0;
	if (animTable.find(animName) != animTable.end())
	{
		int count = (animCnt / animTable[animName][ANIM_TBL_INV] );
		if (animTable[animName][ANIM_TBL_LOOP] || count < animTable[animName][ANIM_TBL_FRAME])	//ٰ�߂��ǂ����A���ڰѐ���菬������
		{
			count = count % animTable[animName][ANIM_TBL_FRAME];
		}
		else    //0,1,2,2,2,2,2����������		�����V���b�g
		{
			count = animTable[animName][ANIM_TBL_FRAME] - 1;
			animEndFlag = true;
			visible = false;	//�@��Ұ��݂̏I���ɏ���
		}
		//((animCnt / animTable[animName][ANIM_TBL_INV]) % animTable[animName][ANIM_TBL_FRAME])
		id = animTable[animName][ANIM_TBL_START_ID] + (int)dir 
			+ count * divCnt.x;	//�������牽�R�}�ڂ��ǂ���
	}
	animCnt++;
	if (visible)
	{
		DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
	}
}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		if (visible)
		{
			//�󂯂��Ƃ�drawOffset�ŕ\�������炵�Ă���
			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
		}
	}
}

const VECTOR2 & Obj::GetPos(void)
{
	return pos;
}
//����string�^��animName
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
	Obj::pos = pos;
}