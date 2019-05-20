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
	//�O�t���[���{�^����������Ă��āA���t���[���͉�����Ă��邩
	if (AttachGamepad_input[pType][eAttachHandle] == PAD_INPUT_ON
		&& AttachGamepad_input_Old[pType][eAttachHandle] == PAD_INPUT_OFF) {
		//���̃t���[���ŗ����ꂽ
		return PAD_PUSH;
	}

	//�{�^����������Ă��Ȃ���
	else if (AttachGamepad_input[pType][eAttachHandle] == PAD_INPUT_OFF) {
		//������Ă��Ȃ�
		return PAD_FREE;
	}


	//�{�^����������Ă��邩
	else if (AttachGamepad_input[pType][eAttachHandle] == PAD_INPUT_OFF
		&& AttachGamepad_input_Old[pType][eAttachHandle] == PAD_INPUT_ON) {
		//������Ă���
		return PAD_PULL;
	}

	//�{�^����������Ă��邩
	else if (AttachGamepad_input[pType][eAttachHandle] == PAD_INPUT_ON) {
		//������Ă���
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

		//�g�p����{�^���݂̂�����
		for (int i = 0; i < CONTROLLER_INPUT_MAX; i++)
		{
			if (pad[p] & (AttachGamepad_pad[i].intButtonHandle)) 		//���̓t���O
			{
				AttachGamepad_input[p][i] = PAD_INPUT_ON;
			}
		}
	}

	//Draw();
	return true;
}

int Game_ctr::Init(void)
{
	//����
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_UP, CONTROLLER_1P_INPUT_UP);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_DOWN, CONTROLLER_1P_INPUT_DOWN);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_LEFT, CONTROLLER_1P_INPUT_LEFT);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_RIGHT, CONTROLLER_1P_INPUT_RIGHT);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_1, CONTROLLER_1P_INPUT_BUTTON_A);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_2, CONTROLLER_1P_INPUT_BUTTON_B);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_3, CONTROLLER_1P_INPUT_BUTTON_X);
	InputAttachmentGamepad(DX_INPUT_PAD1, PAD_INPUT_4, CONTROLLER_1P_INPUT_BUTTON_Y);

	//����
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_UP, CONTROLLER_2P_INPUT_UP);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_DOWN, CONTROLLER_2P_INPUT_DOWN);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_LEFT, CONTROLLER_2P_INPUT_LEFT);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_RIGHT, CONTROLLER_2P_INPUT_RIGHT);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_1, CONTROLLER_2P_INPUT_BUTTON_A);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_2, CONTROLLER_2P_INPUT_BUTTON_B);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_3, CONTROLLER_2P_INPUT_BUTTON_X);
	InputAttachmentGamepad(DX_INPUT_PAD2, PAD_INPUT_4, CONTROLLER_2P_INPUT_BUTTON_Y);

	return 0;
}

void Game_ctr::Draw()
{
	ClsDrawScreen();
	for (int i = 0; i < CONTROLLER_INPUT_MAX; i++)
	{
		if (AttachGamepad_input[P_1][i] == PAD_INPUT_ON)
		{
			DrawFormatString(0, 20, 0xff0000, "PLAYER_1�̃{�^����������܂���");
		}
		if (AttachGamepad_input[P_2][i] == PAD_INPUT_ON)
		{
			DrawFormatString(0, 40, 0xff0000, "PLAYER_2�̃{�^����������܂���");
		}
		if (AttachGamepad_input[P_3][i] == PAD_INPUT_ON)
		{
			DrawFormatString(0, 60, 0xff0000, "PLAYER_3�̃{�^����������܂���");
		}
		if (AttachGamepad_input[P_4][i] == PAD_INPUT_ON)
		{
			DrawFormatString(0, 80, 0xff0000, "PLAYER_4�̃{�^����������܂���");
		}
	}
	ScreenFlip();
}

// ���͊֘A �@�{�^���̃o�C���h
void Game_ctr::InputAttachmentGamepad(int ePadNo, int ePadHandle, int eAttachHandle)
{
	AttachGamepad_pad[eAttachHandle].intPadNo = ePadNo;
	AttachGamepad_pad[eAttachHandle].intButtonHandle = ePadHandle;
}
