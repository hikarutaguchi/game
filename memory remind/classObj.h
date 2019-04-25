#pragma once
#include <list>
#include <memory>
class Obj;

using sharedObj		= std::shared_ptr<Obj>;					// Obj�׽�ւ̼�����߲��
using sharedObjList = std::list<sharedObj>;					// shered_ptr��ؽ�
using sharedListObj = std::shared_ptr<sharedObjList>;		// sharedObjList�����L������Ŏg�p
using weekListObj	= std::weak_ptr<sharedObjList>;			// sharedObjList�����L���Ȃ��Ŏg�p
using ListObj_itr	= sharedObjList::iterator;				// �o�^��ւ̱���,��ڰ��

struct AddObjList
{
	ListObj_itr operator ()(weekListObj objList, sharedObj objPtr)
	{
		objList.lock()->push_back(std::move(objPtr));		// ���L�����ڂ���ؽĂɒǉ�
		ListObj_itr itr = objList.lock()->end();
		itr--;
		return itr;
	}
};