
#include "MapCtl.h"



bool MapCtl::SetUp(const VECTOR2 & size, const VECTOR2 & chipsize	/*const VECTOR2 drawOffset*/)
{
	mapSize = VECTOR2(size.x / chipsize.x, size.y / chipsize.y);
	MapCtl::chipSize = chipsize;

	auto createMap = [=](auto &base, auto&front, auto initNum)
	{
		base.resize(mapSize.x * mapSize.y);
		front.resize(mapSize.y);
		for (unsigned int count = 0; count < front.size(); count++)
		{
			front[count] = &base[mapSize.x * count];
		}

		for (unsigned int j = 0; j < base.size(); j++)
		{
			base[j] = initNum;
		}
	};

	return false;
}

MapCtl::MapCtl()
{

}


MapCtl::~MapCtl()
{

}
