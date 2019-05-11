
#include "index.h"

#define TIMER_COUNT		(__HAL_TIM_GET_COUNTER(&htim6))
#define TIMER_LOAD		(__HAL_TIM_GET_AUTORELOAD(&htim6))
#define TIMER_PSC		((&htim6)->Instance->PSC)

static uint32_t		interrupt_count_now;
static uint32_t		interrupt_duty;
static uint32_t		interrupt_duty_max = 0;
static float		boot_time = 0.f;


/* ---------------------------------------------------------------
	1ms�����Ŋ��荞�ݏ����֐�
--------------------------------------------------------------- */
void Interrupt_Main( void )
{
	// �����Ƀ��C���̊��荞�ݏ������L�q����

}

/* ---------------------------------------------------------------
	���C�����荞�݂̏����ݒ�֐�
--------------------------------------------------------------- */
void Interrupt_Initialize( void )
{
	HAL_TIM_Base_Start_IT( &htim6 );
}

/* ---------------------------------------------------------------
	���荞�ݑO�����֐�
--------------------------------------------------------------- */
void Interrupt_PreProcess( void )
{
	static uint32_t		interrupt_count_old = 0;
	static uint64_t		boot_time_count = 0;

	interrupt_count_now = TIMER_COUNT;
	boot_time_count += (uint16_t)(interrupt_count_now - interrupt_count_old);
	interrupt_count_old = interrupt_count_now;
	boot_time = (float)boot_time_count / (float)(HAL_RCC_GetPCLK2Freq() / TIMER_PSC);
}

/* ---------------------------------------------------------------
	���荞�݌㏈���֐�
--------------------------------------------------------------- */
void Interrupt_PostProcess( void )
{
	interrupt_duty = (TIMER_COUNT - interrupt_count_now) * 1000 / TIMER_LOAD;
	interrupt_duty_max = MAX( interrupt_duty_max, interrupt_duty );
}

/* ---------------------------------------------------------------
	���荞�ݎ����ɐ�߂�Ăяo���ʒu�܂ł̏������Ԃ̊������擾����֐�
--------------------------------------------------------------- */
uint16_t Interrupt_GetDuty( void )
{
	return interrupt_duty;
}

/* ---------------------------------------------------------------
	��L�����̍ő�l���擾����֐�
--------------------------------------------------------------- */
uint16_t Interrupt_GetDuty_Max( void )
{
	return interrupt_duty_max;
}

/* ---------------------------------------------------------------
	�}�C�R���N��������̌o�ߎ��Ԃ��擾����֐�
--------------------------------------------------------------- */
float Interrupt_GetBootTime( void )
{
	return boot_time;
}
