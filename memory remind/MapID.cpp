#include "MapID.h"

MAP_ID operator+(MAP_ID m, int j)
{
	return static_cast<MAP_ID>(static_cast<int>(m) + j);
}

MAP_ID operator-(MAP_ID m, int j)
{
	return static_cast<MAP_ID>(static_cast<int>(m) - j);
}