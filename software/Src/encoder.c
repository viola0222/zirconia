
#include "index.h"

#define ENC_CNT_L		(TIM2 -> CNT)
#define ENC_CNT_R		(TIM3 -> CNT)

#define ENC_ZERO		(20000)			/* �G���R�[�_�̏����l */
#define ENC_RESOLUTION 	(1024 - 1)		/* �G���R�[�_�̕���\ */

/* ---------------------------------------------------------------
	�ʑ��W�����[�h�̃^�C�}�[���J�n����֐�
--------------------------------------------------------------- */
void Encoder_Initialize( void )
{
	HAL_TIM_Encoder_Start( &htim2, TIM_CHANNEL_ALL );
	HAL_TIM_Encoder_Start( &htim3, TIM_CHANNEL_ALL );
}

/* ---------------------------------------------------------------
	���^�C���̈ʑ��W���J�E���g������������֐�
--------------------------------------------------------------- */
void Encoder_ResetCount_Left( void )
{
	ENC_CNT_L = ENC_ZERO;
}

/* ---------------------------------------------------------------
	�E�^�C���̈ʑ��W���J�E���g������������֐�
--------------------------------------------------------------- */
void Encoder_ResetCount_Right( void )
{
	ENC_CNT_R = ENC_ZERO;
}

/* ---------------------------------------------------------------
	���^�C���̊p�x���擾����֐�[rad]
--------------------------------------------------------------- */
float Encoder_GetAngle_Left( void )
{
	return(2 * PI * (float)( (int32_t)ENC_CNT_L - (int32_t)ENC_ZERO ) / (float)ENC_RESOLUTION);
}

/* ---------------------------------------------------------------
	�E�^�C���̊p�x���擾����֐�[rad]
--------------------------------------------------------------- */
float Encoder_GetAngle_Right( void )
{
	return(2 * PI * (float)( (int32_t)ENC_ZERO - (int32_t)ENC_CNT_R ) / (float)ENC_RESOLUTION);
}
