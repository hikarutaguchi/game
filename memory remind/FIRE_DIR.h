#pragma once

enum class FIRE_DIR{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};

//enumｸﾗｽの範囲for文を使う際にはこの４つが必要,enumｸﾗｽを使うたびに必要,面倒くさいのでtemplate化する。
FIRE_DIR begin(FIRE_DIR);
FIRE_DIR end(FIRE_DIR);
FIRE_DIR operator ++(FIRE_DIR& dir);
FIRE_DIR operator *(FIRE_DIR& dir);

