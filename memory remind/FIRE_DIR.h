#pragma once

enum class FIRE_DIR{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};

//enum�׽�͈̔�for�����g���ۂɂ͂��̂S���K�v,enum�׽���g�����тɕK�v,�ʓ|�������̂�template������B
FIRE_DIR begin(FIRE_DIR);
FIRE_DIR end(FIRE_DIR);
FIRE_DIR operator ++(FIRE_DIR& dir);
FIRE_DIR operator *(FIRE_DIR& dir);

