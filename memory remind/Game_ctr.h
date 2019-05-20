#pragma once
#include <array>

#define PAD_BUTTON_MAX	28	// �{�^������
#define PAD_INPUT_ON	1	// �����ꂽ
#define PAD_INPUT_OFF	0	// ������ĂȂ��B

enum eKeyInout
{
	INPUT_UP,			// �\���L�[��
	INPUT_DOWN,			// �\���L�[��
	INPUT_LEFT,			// �\���L�[��
	INPUT_RIGHT,		// �\���L�[�E
	INPUT_BUTTON_A,		// �{�^���P
	INPUT_BUTTON_B,		// �{�^���Q
	INPUT_BUTTON_X,		// �{�^���R
	INPUT_BUTTON_Y,		// �{�^���S

	CONTROLLER_INPUT_MAX,	// �g�p�{�^������
};

enum PAD_TYPE {
	PAD_PUSH,		//�����ꂽ�Ƃ�
	PAD_FREE,		//������Ă�Ƃ�
	PAD_PULL,		//�������Ƃ�
	PAD_HOLD,		//�����Ă�Ƃ�
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
	void InputAttachmentGamepad(int ePadHandle, int eAttachHandle);

	struct tyAttachment AttachGamepad_pad[CONTROLLER_INPUT_MAX];	//�W���C�p�b�h�̂ƃA�^�b�`�l

	bool Updata(void);								// ���X�V

	const PAD_TYPE & GetCtr(int eAttachHandle, P_TYPE pType) const;

private:
	int Init(void);
	int pad[CONTROLLER_MAX];
	int AttachGamepad_input[CONTROLLER_MAX][CONTROLLER_INPUT_MAX];	//�p�b�h�̓��͏��(�����ꂽ���ǂ���)
	int AttachGamepad_input_Old[CONTROLLER_MAX][CONTROLLER_INPUT_MAX];	//�p�b�h�̓��͏��(�����ꂽ���ǂ���)
};