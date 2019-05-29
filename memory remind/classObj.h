#pragma once
#include <list>
#include <memory>
class Obj;
class Obj2;

using sharedObj		= std::shared_ptr<Obj>;					// Objｸﾗｽへのｼｪｱﾄﾞﾎﾟｲﾝﾀ
using sharedObjList = std::list<sharedObj>;					// shered_ptrのﾘｽﾄ
using sharedListObj = std::shared_ptr<sharedObjList>;		// sharedObjListを所有権ありで使用
using weekListObj	= std::weak_ptr<sharedObjList>;			// sharedObjListを所有権なしで使用
using ListObj_itr	= sharedObjList::iterator;				// 登録先へのｱｸｾｽ,ｲﾃﾚｰﾀｰ

//using sharedObj2 = std::shared_ptr<Obj2>;					// Objｸﾗｽへのｼｪｱﾄﾞﾎﾟｲﾝﾀ
//using sharedObjList2 = std::list<sharedObj2>;					// shered_ptrのﾘｽﾄ
//using sharedListObj2 = std::shared_ptr<sharedObjList2>;		// sharedObjListを所有権ありで使用
//using weekListObj2 = std::weak_ptr<sharedObjList2>;			// sharedObjListを所有権なしで使用
//using ListObj_itr2 = sharedObjList2::iterator;				// 登録先へのｱｸｾｽ,ｲﾃﾚｰﾀｰ

struct AddObjList
{
	ListObj_itr operator ()(weekListObj objList, sharedObj objPtr)
	{
		objList.lock()->push_back(std::move(objPtr));		// 所有権を移しつつﾘｽﾄに追加
		ListObj_itr itr = objList.lock()->end();
		itr--;
		return itr;
	}
};

//struct AddObjList2
//{
//	ListObj_itr2 operator ()(weekListObj2 objList2, sharedObj2 objPtr)
//	{
//		objList2.lock()->push_back(std::move(objPtr));		// 所有権を移しつつﾘｽﾄに追加
//		ListObj_itr2 itr2 = objList2.lock()->end();
//		itr2--;
//		return itr2;
//	}
//};