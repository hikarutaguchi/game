#include "DxLib.h"
#include "Game_ctr.h"



Game_ctr::Game_ctr()
{
	Init();
}


Game_ctr::~Game_ctr()
{

}

const PAD_TYPE & Game_ctr::GetCtr(int eAttachHandle) const
{
	//前フレームボタンが離されていて、現フレームは押されているか
	if (AttachGamepad_input[eAttachHandle] == PAD_INPUT_ON
		&& AttachGamepad_input_Old[eAttachHandle] == PAD_INPUT_OFF) {
		//このフレームで離された
		return PAD_PUSH;
	}

	//ボタンが押されていないか
	else if (AttachGamepad_input[eAttachHandle] == PAD_INPUT_OFF) {
		//押されていない
		return PAD_FREE;
	}


	//ボタンが押されているか
	else if (AttachGamepad_input[eAttachHandle] == PAD_INPUT_OFF
		&& AttachGamepad_input_Old[eAttachHandle] == PAD_INPUT_ON) {
		//押されている
		return PAD_PULL;
	}

	//ボタンが押されているか
	else if (AttachGamepad_input[eAttachHandle] == PAD_INPUT_ON) {
		//押されている
		return PAD_HOLD;
	}
}

bool Game_ctr::Updata()
{

	//入力情報の初期化
	memset(AttachGamepad_input, 0, sizeof(AttachGamepad_input));

	//過去情報を格納
	memcpy(AttachGamepad_input_Old, &AttachGamepad_input, sizeof(AttachGamepad_input));

	//使用するボタンのみを検索
	for (int i = 0; i < CONTROLLER_INPUT_MAX; i++)
	{
		int Pad = GetJoypadInputState(AttachGamepad_pad[i].intPadNo);		//設定されているジョイパッドの入力情報を取得

		if (Pad & (AttachGamepad_pad[i].intButtonHandle)) 		//入力フラグ
		{
			AttachGamepad_input[i] = PAD_INPUT_ON;
		}
	}
	return true;
}

int Game_ctr::Init(void)
{

	//一台目
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_UP, CONTROLLER_1P_INPUT_UP);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_DOWN, CONTROLLER_1P_INPUT_DOWN);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_LEFT, CONTROLLER_1P_INPUT_LEFT);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_RIGHT, CONTROLLER_1P_INPUT_RIGHT);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_1, CONTROLLER_1P_INPUT_BUTTON_A);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_2, CONTROLLER_1P_INPUT_BUTTON_B);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_3, CONTROLLER_1P_INPUT_BUTTON_X);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_4, CONTROLLER_1P_INPUT_BUTTON_Y);

	//二台目
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_UP, CONTROLLER_2P_INPUT_UP);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_DOWN, CONTROLLER_2P_INPUT_DOWN);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_LEFT, CONTROLLER_2P_INPUT_LEFT);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_RIGHT, CONTROLLER_2P_INPUT_RIGHT);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_1, CONTROLLER_2P_INPUT_BUTTON_A);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_2, CONTROLLER_2P_INPUT_BUTTON_B);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_3, CONTROLLER_2P_INPUT_BUTTON_X);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_4, CONTROLLER_2P_INPUT_BUTTON_Y);

	Draw();

	return 0;
}

void Game_ctr::Draw()
{

	//使用するボタンのみを検索
	for (int i = 0; i < CONTROLLER_INPUT_MAX; i++) {
		//ボタンは押されているか
		if (AttachGamepad_input[i] == PAD_INPUT_ON) {
			//ログ出力
			AppLogAdd("[%d]が押されました\n", i);
		}
	}
	ScreenFlip();

}

// 入力関連 　ボタンのバインド
void Game_ctr::InputAttachmentGamepad(int ePadNo, int ePadHandle, int eAttachHandle)
{
	AttachGamepad_pad[eAttachHandle].intPadNo = ePadNo;
	AttachGamepad_pad[eAttachHandle].intButtonHandle = ePadHandle;
}
