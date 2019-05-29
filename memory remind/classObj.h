#pragma once
#include <list>
#include <memory>
class Obj;
class Obj2;

using sharedObj		= std::shared_ptr<Obj>;					// Obj�׽�ւ̼�����߲��
using sharedObjList = std::list<sharedObj>;					// shered_ptr��ؽ�
using sharedListObj = std::shared_ptr<sharedObjList>;		// sharedObjList�����L������Ŏg�p
using weekListObj	= std::weak_ptr<sharedObjList>;			// sharedObjList�����L���Ȃ��Ŏg�p
using ListObj_itr	= sharedObjList::iterator;				// �o�^��ւ̱���,��ڰ��

//using sharedObj2 = std::shared_ptr<Obj2>;					// Obj�׽�ւ̼�����߲��
//using sharedObjList2 = std::list<sharedObj2>;					// shered_ptr��ؽ�
//using sharedListObj2 = std::shared_ptr<sharedObjList2>;		// sharedObjList�����L������Ŏg�p
//using weekListObj2 = std::weak_ptr<sharedObjList2>;			// sharedObjList�����L���Ȃ��Ŏg�p
//using ListObj_itr2 = sharedObjList2::iterator;				// �o�^��ւ̱���,��ڰ��

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

//struct AddObjList2
//{
//	ListObj_itr2 operator ()(weekListObj2 objList2, sharedObj2 objPtr)
//	{
//		objList2.lock()->push_back(std::move(objPtr));		// ���L�����ڂ���ؽĂɒǉ�
//		ListObj_itr2 itr2 = objList2.lock()->end();
//		itr2--;
//		return itr2;
//	}
//};