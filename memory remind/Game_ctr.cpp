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
	//�O�t���[���{�^����������Ă��āA���t���[���͉�����Ă��邩
	if (AttachGamepad_input[eAttachHandle] == PAD_INPUT_ON
		&& AttachGamepad_input_Old[eAttachHandle] == PAD_INPUT_OFF) {
		//���̃t���[���ŗ����ꂽ
		return PAD_PUSH;
	}

	//�{�^����������Ă��Ȃ���
	else if (AttachGamepad_input[eAttachHandle] == PAD_INPUT_OFF) {
		//������Ă��Ȃ�
		return PAD_FREE;
	}


	//�{�^����������Ă��邩
	else if (AttachGamepad_input[eAttachHandle] == PAD_INPUT_OFF
		&& AttachGamepad_input_Old[eAttachHandle] == PAD_INPUT_ON) {
		//������Ă���
		return PAD_PULL;
	}

	//�{�^����������Ă��邩
	else if (AttachGamepad_input[eAttachHandle] == PAD_INPUT_ON) {
		//������Ă���
		return PAD_HOLD;
	}
}

bool Game_ctr::Updata()
{

	//���͏��̏�����
	memset(AttachGamepad_input, 0, sizeof(AttachGamepad_input));

	//�ߋ������i�[
	memcpy(AttachGamepad_input_Old, &AttachGamepad_input, sizeof(AttachGamepad_input));

	//�g�p����{�^���݂̂�����
	for (int i = 0; i < CONTROLLER_INPUT_MAX; i++)
	{
		int Pad = GetJoypadInputState(AttachGamepad_pad[i].intPadNo);		//�ݒ肳��Ă���W���C�p�b�h�̓��͏����擾

		if (Pad & (AttachGamepad_pad[i].intButtonHandle)) 		//���̓t���O
		{
			AttachGamepad_input[i] = PAD_INPUT_ON;
		}
	}
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

	Draw();

	return 0;
}

void Game_ctr::Draw()
{

	//�g�p����{�^���݂̂�����
	for (int i = 0; i < CONTROLLER_INPUT_MAX; i++) {
		//�{�^���͉�����Ă��邩
		if (AttachGamepad_input[i] == PAD_INPUT_ON) {
			//���O�o��
			AppLogAdd("[%d]��������܂���\n", i);
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
