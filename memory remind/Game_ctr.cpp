#include "DxLib.h"
#include "Game_ctr.h"



Game_ctr::Game_ctr()
{
	Init();
}


Game_ctr::~Game_ctr()
{

}

const PAD_TYPE & Game_ctr::GetCtr(int eAttachHandle, P_TYPE pType) const
{
	//前フレームボタンが離されていて、現フレームは押されているか
	if (AttachGamepad_input[pType][eAttachHandle] == PAD_INPUT_ON
		&& AttachGamepad_input_Old[pType][eAttachHandle] == PAD_INPUT_OFF) {
		//このフレームで離された
		return PAD_PUSH;
	}

	//ボタンが押されていないか
	else if (AttachGamepad_input[pType][eAttachHandle] == PAD_INPUT_OFF) {
		//押されていない
		return PAD_FREE;
	}


	//ボタンが押されているか
	else if (AttachGamepad_input[pType][eAttachHandle] == PAD_INPUT_OFF
		&& AttachGamepad_input_Old[pType][eAttachHandle] == PAD_INPUT_ON) {
		//押されている
		return PAD_PULL;
	}

	//ボタンが押されているか
	else if (AttachGamepad_input[pType][eAttachHandle] == PAD_INPUT_ON) {
		//押されている
		return PAD_HOLD;
	}
}

bool Game_ctr::Updata()
{
	for (int p = 0; p < GetJoypadNum(); p++)
	{
		for (int i = 0; i < CONTROLLER_INPUT_MAX; i++)
		{

			AttachGamepad_input_Old[p][i] = AttachGamepad_input[p][i];

			AttachGamepad_input[p][i] = PAD_INPUT_OFF;
		}
	}
	for (int p = 0; p < GetJoypadNum(); p++)
	{
		pad[p] = GetJoypadInputState(DX_INPUT_PAD1 + p);

		//使用するボタンのみを検索
		for (int i = 0; i < CONTROLLER_INPUT_MAX; i++)
		{
			if (pad[p] & (AttachGamepad_pad[i].intButtonHandle)) 		//入力フラグ
			{
				AttachGamepad_input[p][i] = PAD_INPUT_ON;
			}
		}
	}
	return true;
}

int Game_ctr::Init(void)
{
	InputAttachmentGamepad(PAD_INPUT_UP, INPUT_UP);
	InputAttachmentGamepad(PAD_INPUT_DOWN, INPUT_DOWN);
	InputAttachmentGamepad(PAD_INPUT_LEFT, INPUT_LEFT);
	InputAttachmentGamepad(PAD_INPUT_RIGHT, INPUT_RIGHT);
	InputAttachmentGamepad(PAD_INPUT_1, INPUT_BUTTON_A);
	InputAttachmentGamepad(PAD_INPUT_2, INPUT_BUTTON_B);
	InputAttachmentGamepad(PAD_INPUT_3,INPUT_BUTTON_X);
	InputAttachmentGamepad(PAD_INPUT_4,INPUT_BUTTON_Y);

	return 0;
}

// 入力関連 　ボタンのバインド
void Game_ctr::InputAttachmentGamepad(int ePadHandle, int eAttachHandle)
{
	AttachGamepad_pad[eAttachHandle].intButtonHandle = ePadHandle;
}
