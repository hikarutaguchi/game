#pragma once
#include <memory>


#define GAME_SCREEN_X 120			// ｹﾞｰﾑｴﾘｱ表示のｵﾌｾｯﾄ横
#define GAME_SCREEN_Y 120			// ｹﾞｰﾑｴﾘｱ表示のｵﾌｾｯﾄ縦

#define GAME_SCREEN_SIZE_X 960		// ｹﾞｰﾑｴﾘｱｻｲｽﾞ横
#define GAME_SCREEN_SIZE_Y 704		// ｹﾞｰﾑｴﾘｱｻｲｽﾞ縦

#define SCREEN_SIZE_X 1200			// 画面解像度横
#define SCREEN_SIZE_Y 944			// 画面解像度縦

#define CHIP_SIZE 64				// ﾏｽ目ｻｲｽﾞ

class Game_ctr;						// Game_ctrあとから登場
class BaseScene;					// BaseSceneがあとから出てくるぞ宣言
using unique_Base = std::unique_ptr<BaseScene>;


class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base Updata(unique_Base own, Game_ctr &controller) = 0;	// 純粋仮想関数UpDate
private:
	virtual int Init(void) = 0;														// 純粋仮想関数Init
};


