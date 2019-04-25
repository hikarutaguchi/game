#include <type_traits>
#include "FIRE_DIR.h"

FIRE_DIR begin(FIRE_DIR)
{
	return FIRE_DIR::LEFT;
}

FIRE_DIR end(FIRE_DIR)
{
	return FIRE_DIR::MAX;
}

FIRE_DIR operator++(FIRE_DIR & dir)
{

	return dir = FIRE_DIR(std::underlying_type<FIRE_DIR>::type(dir) + 1);	//指定したやつの基底の型を調べる
}

FIRE_DIR operator*(FIRE_DIR & dir)
{
	return dir;
}
