#pragma once

enum class MAP_ID {			// image.mapÇéQè∆
	FLOOR1,
	FLOOR2,
	TRAP_1,
	TRAP_2,
	TRAP_3,
	TRAP_4,
	TRAP_5,
	TRAP_6,
	TRAP_7,
	MAX
};
MAP_ID operator+(MAP_ID m, int j);
MAP_ID operator-(MAP_ID m, int j);

#define ITEM_ID_START MAP_ID::ITEM_BOMB
#define ITEM_MAX (static_cast<int>(MAP_ID::MAX) - static_cast<int>(ITEM_ID_START))