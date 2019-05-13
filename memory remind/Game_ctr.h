#pragma once
#include <array>

#define PAD_BUTTON_MAX	28	// ボタン総数
#define PAD_INPUT_ON	1	// 押された
#define PAD_INPUT_OFF	0	// 押されてない。

enum eKeyInout
{
	CONTROLLER_1P_INPUT_UP,	// 十字キー上(1P)
	CONTROLLER_1P_INPUT_DOWN,	// 十字キー下(1P)
	CONTROLLER_1P_INPUT_LEFT,	// 十字キー左(1P)
	CONTROLLER_1P_INPUT_RIGHT,	// 十字キー右(1P)
	CONTROLLER_1P_INPUT_BUTTON_A,	// ボタン１(1P)
	CONTROLLER_1P_INPUT_BUTTON_B,	// ボタン２(1P)
	CONTROLLER_1P_INPUT_BUTTON_X,	// ボタン３(1P)
	CONTROLLER_1P_INPUT_BUTTON_Y,	// ボタン４(1P)

	CONTROLLER_2P_INPUT_UP,	// 十字キー上(2P)
	CONTROLLER_2P_INPUT_DOWN,	// 十字キー下(2P)
	CONTROLLER_2P_INPUT_LEFT,	// 十字キー左(2P)
	CONTROLLER_2P_INPUT_RIGHT,	// 十字キー右(2P)
	CONTROLLER_2P_INPUT_BUTTON_A,	// ボタン１(2P)
	CONTROLLER_2P_INPUT_BUTTON_B,	// ボタン２(2P)
	CONTROLLER_2P_INPUT_BUTTON_X,	// ボタン３(2P)
	CONTROLLER_2P_INPUT_BUTTON_Y,	// ボタン４(2P)

	CONTROLLER_INPUT_MAX,	// 使用ボタン総数
};

enum PAD_TYPE {
	PAD_PUSH,
	PAD_FREE,
	PAD_PULL,
	PAD_HOLD,
	PAD_MAX
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
	void InputAttachmentGamepad(int ePadNo, int ePadHandle, int eAttachHandle);

	struct tyAttachment AttachGamepad_pad[CONTROLLER_INPUT_MAX];	//ジョイパッドのとアタッチ値

	bool Updata(void);								// 情報更新

	const PAD_TYPE & GetCtr(int eAttachHandle) const;

private:
	int Init(void);
	void Draw();
	int AttachGamepad_input[CONTROLLER_INPUT_MAX];	//パッドの入力情報(押されたかどうか)
	int AttachGamepad_input_Old[CONTROLLER_INPUT_MAX];	//パッドの入力情報(押されたかどうか)
};

