#pragma once
#include <type_traits>
#include <memory>
#include <vector>
#include <array>
#include "VECTOR2.h"

#define lpMapCtl MapCtl::GetInstance()


class MapCtl
{
public:
	// Ã“I‚È¼İ¸ŞÙÄİ

	static MapCtl &GetInstance(void)
	{
		static MapCtl s_instance;
		return s_instance;
	}
	bool SetUp(const VECTOR2& size, const VECTOR2& chipsize /*const VECTOR2 drawOffset*/);	// Ï¯Ìß‚Ì¾¯Ä±¯Ìß
private:
	MapCtl();
	~MapCtl();

	std::vector<MAP_ID>	 mapDataBase;
	std::vector<MAP_ID*> mapData;


	VECTOR2 mapSize;	// Ï¯Ìß»²½Ş
	VECTOR2 chipSize;	// Á¯Ìß»²½Ş
};

