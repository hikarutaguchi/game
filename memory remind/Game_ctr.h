#pragma once
#include <array>

#define PAD_BUTTON_MAX	28	// �{�^������
#define PAD_INPUT_ON	1	// �����ꂽ
#define PAD_INPUT_OFF	0	// ������ĂȂ��B

enum eKeyInout
{
	CONTROLLER_1P_INPUT_UP,	// �\���L�[��(1P)
	CONTROLLER_1P_INPUT_DOWN,	// �\���L�[��(1P)
	CONTROLLER_1P_INPUT_LEFT,	// �\���L�[��(1P)
	CONTROLLER_1P_INPUT_RIGHT,	// �\���L�[�E(1P)
	CONTROLLER_1P_INPUT_BUTTON_A,	// �{�^���P(1P)
	CONTROLLER_1P_INPUT_BUTTON_B,	// �{�^���Q(1P)
	CONTROLLER_1P_INPUT_BUTTON_X,	// �{�^���R(1P)
	CONTROLLER_1P_INPUT_BUTTON_Y,	// �{�^���S(1P)

	CONTROLLER_2P_INPUT_UP,	// �\���L�[��(2P)
	CONTROLLER_2P_INPUT_DOWN,	// �\���L�[��(2P)
	CONTROLLER_2P_INPUT_LEFT,	// �\���L�[��(2P)
	CONTROLLER_2P_INPUT_RIGHT,	// �\���L�[�E(2P)
	CONTROLLER_2P_INPUT_BUTTON_A,	// �{�^���P(2P)
	CONTROLLER_2P_INPUT_BUTTON_B,	// �{�^���Q(2P)
	CONTROLLER_2P_INPUT_BUTTON_X,	// �{�^���R(2P)
	CONTROLLER_2P_INPUT_BUTTON_Y,	// �{�^���S(2P)

	CONTROLLER_INPUT_MAX,	// �g�p�{�^������
};

enum PAD_TYPE {
	PAD_PUSH,
	PAD_FREE,
	PAD_PULL,
	PAD_HOLD,
	PAD_MAX
};

//�W���C�p�b�h�i�[�p�\����
struct tyAttachment {
	int intPadNo;	//�p�b�h�ԍ�
	int intButtonHandle;	//�{�^���n���h��
};

using PAD_ARRAY = std::array<int, CONTROLLER_INPUT_MAX>;


class Game_ctr
{
public:
	Game_ctr();
	~Game_ctr();

	//�L�[�Ƃ̊��蓖��
	void InputAttachmentGamepad(int ePadNo, int ePadHandle, int eAttachHandle);

	struct tyAttachment AttachGamepad_pad[CONTROLLER_INPUT_MAX];	//�W���C�p�b�h�̂ƃA�^�b�`�l

	bool Updata(void);								// ���X�V

	const PAD_TYPE & GetCtr(int eAttachHandle) const;

private:
	int Init(void);
	void Draw();
	int AttachGamepad_input[CONTROLLER_INPUT_MAX];	//�p�b�h�̓��͏��(�����ꂽ���ǂ���)
	int AttachGamepad_input_Old[CONTROLLER_INPUT_MAX];	//�p�b�h�̓��͏��(�����ꂽ���ǂ���)
};

