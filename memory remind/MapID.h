#pragma once

enum class MAP_ID {			// image.map‚ðŽQÆ
	CUR,				// ¶°¿Ù
	FLOOR1,
	FLOOR2,
	BOMB,
	NON,
	WALL1,
	WALL2,
	BLOCK,			// ‰ó‚¹‚é‚â‚Â	
	ITEM_BOMB,
	ITEM_FIRE,
	ITEM_SPEED,		
	ITEM_WALL_PASS,
	//ITEM_CTL,		// ‹N”šºÝÄÛ°Ù
	//ITEM_BOMB_THROW,// ”š’e“Š‚°
	//ITEM_FIRE_GUARD,// ‰Š¶Þ°ÄÞ
	//ITEM_RANDOM,	// ±²ÃÑ×ÝÀÞÑoŒ»
	MAX
};
MAP_ID operator+(MAP_ID m, int j);
MAP_ID operator-(MAP_ID m, int j);

#define ITEM_ID_START MAP_ID::ITEM_BOMB
#define ITEM_MAX (static_cast<int>(MAP_ID::MAX) - static_cast<int>(ITEM_ID_START))