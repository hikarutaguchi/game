#pragma once
#include <array>

#define PAD_BUTTON_MAX	28	// ボタン総数
#define PAD_INPUT_ON	1	// 押された
#define PAD_INPUT_OFF	0	// 押されてない。

enum eKeyInout
{
	INPUT_UP,			// 十字キー上
	INPUT_DOWN,			// 十字キー下
	INPUT_LEFT,			// 十字キー左
	INPUT_RIGHT,		// 十字キー右
	INPUT_BUTTON_A,		// ボタン１
	INPUT_BUTTON_B,		// ボタン２
	INPUT_BUTTON_X,		// ボタン３
	INPUT_BUTTON_Y,		// ボタン４

	CONTROLLER_INPUT_MAX,	// 使用ボタン総数
};

enum PAD_TYPE {
	PAD_PUSH,		//押されたとき
	PAD_FREE,		//離されてるとき
	PAD_PULL,		//離したとき
	PAD_HOLD,		//押してるとき
	PAD_MAX			//MAX
};

enum P_TYPE
{
	CONTROLLER_P1,
	CONTROLLER_P2,
	CONTROLLER_P3,
	CONTROLLER_P4,
	CONTROLLER_MAX
};

//ジョイパッド格納用構造体
struct tyAttachment {
	int intPadNo;	//パッド番号
	int intButtonHandle;	//ボタンハンドル
};

using PAD_ARRAY = std::array<int, CONTROLLER_INPUT_MAX>;


class Game_ctr
{
public:
	Game_ctr();
	~Game_ctr();

	//キーとの割り当て
	void InputAttachmentGamepad(int ePadHandle, int eAttachHandle);

	struct tyAttachment AttachGamepad_pad[CONTROLLER_INPUT_MAX];	//ジョイパッドのとアタッチ値

	bool Updata(void);								// 情報更新

	const PAD_TYPE & GetCtr(int eAttachHandle, P_TYPE pType) const;

private:
	int Init(void);
	int pad[CONTROLLER_MAX];
	int AttachGamepad_input[CONTROLLER_MAX][CONTROLLER_INPUT_MAX];	//パッドの入力情報(押されたかどうか)
	int AttachGamepad_input_Old[CONTROLLER_MAX][CONTROLLER_INPUT_MAX];	//パッドの入力情報(押されたかどうか)
};