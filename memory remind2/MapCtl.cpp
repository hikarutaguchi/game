#include <type_traits>
#include <memory>
#include "DxLib.h"
#include "MapCtl.h"



bool MapCtl::SetUp(const VECTOR2 & size, const VECTOR2 & chipsize	/*const VECTOR2 drawOffset*/)
{
	mapSize = VECTOR2(size.x / chipsize.x, size.y / chipsize.y);
	MapCtl::chipSize = chipsize;

	auto createMap = [=](auto& base, auto& front, auto initNum) {

		base.resize(mapSize.x * mapSize.y);	//—v‘f‚Æ‚µ‚Ä‘S‘Ì‚Ì»²½Ş‚ğŠm•Û
		front.resize(mapSize.y);			//c‚É‰½ŒÂ‚¢‚ê‚é‚©
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
