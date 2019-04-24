#include <type_traits>
#include <memory>
#include "DxLib.h"
#include "MapCtl.h"



bool MapCtl::SetUp(const VECTOR2 & size, const VECTOR2 & chipsize	/*const VECTOR2 drawOffset*/)
{
	mapSize = VECTOR2(size.x / chipsize.x, size.y / chipsize.y);
	MapCtl::chipSize = chipsize;

	auto createMap = [=](auto& base, auto& front, auto initNum) {

		base.resize(mapSize.x * mapSize.y);	//要素として全体のｻｲｽﾞを確保
		front.resize(mapSize.y);			//縦に何個いれるか
		for (unsigned int count = 0; count < front.size(); count++)
		{
			front[count] = &base[mapSize.x * count];
		}

		for (unsigned int j = 0; j < base.size(); j++)
		{
			base[j] = initNum;
		}
	};

	createMap(mapDataBase, mapData, MAP_ID::FLOOR1);

	return false;
}

MapCtl::MapCtl()
{

}


MapCtl::~MapCtl()
{

}
