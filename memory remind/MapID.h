#pragma once

enum class MAP_ID {			// image.mapÇéQè∆
	YUKA,
	IWA,
	HOLE,
	UNTI,
	EKI,
	NULLL,
	WIND,
	MAGIC,
	MAGIC1,
	BORN,
	ESA,
	TOOL,
	MAX
};
MAP_ID operator+(MAP_ID m, int j);
MAP_ID operator-(MAP_ID m, int j);

#define ITEM_ID_START MAP_ID::EKI
#define ITEM_MAX (static_cast<int>(MAP_ID::MAX) - static_cast<int>(ITEM_ID_START))