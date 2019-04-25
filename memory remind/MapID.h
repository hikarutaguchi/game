#pragma once

enum class MAP_ID {			// image.map���Q��
	CUR,				// ����
	FLOOR1,
	FLOOR2,
	BOMB,
	NON,
	WALL1,
	WALL2,
	BLOCK,			// �󂹂���	
	ITEM_BOMB,
	ITEM_FIRE,
	ITEM_SPEED,		
	ITEM_WALL_PASS,
	//ITEM_CTL,		// �N�����۰�
	//ITEM_BOMB_THROW,// ���e����
	//ITEM_FIRE_GUARD,// ���ް��
	//ITEM_RANDOM,	// ��������яo��
	MAX
};
MAP_ID operator+(MAP_ID m, int j);
MAP_ID operator-(MAP_ID m, int j);

#define ITEM_ID_START MAP_ID::ITEM_BOMB
#define ITEM_MAX (static_cast<int>(MAP_ID::MAX) - static_cast<int>(ITEM_ID_START))