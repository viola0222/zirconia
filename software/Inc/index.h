
#ifndef INDEX_H_
#define INDEX_H_

#include <stdio.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* �֗��Ȓ萔�Q */
#define G					(9.80665f)					// �d�ʉ����x[m/s^2]
#define PI					(3.1415926f)				// �~����
#define SQRT2				(1.41421356237f)			// ���[�g2
#define SQRT3				(1.73205080757f)			// ���[�g3
#define SQRT5				(2.2360679775f)				// ���[�g5
#define SQRT7				(2.64575131106f)			// ���[�g7

/* �֗��ȃ}�N���֐��Q */
#define DEG2RAD(x)			(((x)/180.0f)*PI)			// �x���@���烉�W�A���ɕϊ�
#define RAD2DEG(x)			(180.0f*((x)/PI))			// ���W�A������x���@�ɕϊ�
#define SWAP(a, b) 			((a != b) && (a += b, b = a - b, a -= b))
#define ABS(x) 				((x) < 0 ? -(x) : (x))		// ��Βl
#define SIGN(x)				((x) < 0 ? -1 : 1)			// ����
#define MAX(a, b) 			((a) > (b) ? (a) : (b))		// 2�̂����傫������Ԃ��܂�
#define MIN(a, b) 			((a) < (b) ? (a) : (b))		// 2�̂�������������Ԃ��܂�
#define MAX3(a, b, c) 		((a) > (MAX(b, c)) ? (a) : (MAX(b, c)))
#define MIN3(a, b, c) 		((a) < (MIN(b, c)) ? (a) : (MIN(b, c)))

/* LED�֐��Q */
#define LED_YELLOW_ON()		HAL_GPIO_WritePin( LED_Yellow_GPIO_Port, LED_Yellow_Pin, GPIO_PIN_SET)		// ��LED��_������
#define LED_YELLOW_OFF()	HAL_GPIO_WritePin( LED_Yellow_GPIO_Port, LED_Yellow_Pin, GPIO_PIN_RESET)	// ��LED����������
#define LED_YELLOW_TOGGLE()	HAL_GPIO_TogglePin(LED_Yellow_GPIO_Port, LED_Yellow_Pin)					// ���̊֐����ĂԂ��тɉ�LED�̓_���Ə�����؂�ւ���
#define LED_RED_ON()		HAL_GPIO_WritePin( LED_Red_GPIO_Port, 	 LED_Red_Pin, 	 GPIO_PIN_SET)		// ��LED��_������
#define LED_RED_OFF()		HAL_GPIO_WritePin( LED_Red_GPIO_Port, 	 LED_Red_Pin,    GPIO_PIN_RESET)	// ��LED����������
#define LED_RED_TOGGLE()	HAL_GPIO_TogglePin(LED_Red_GPIO_Port, 	 LED_Red_Pin)						// ���̊֐����ĂԂ��тɐ�LED�̓_���Ə�����؂�ւ���
#define LED_GREEN_ON()		HAL_GPIO_WritePin( LED_Green_GPIO_Port,  LED_Green_Pin,  GPIO_PIN_SET)		// ��LED��_������
#define LED_GREEN_OFF()		HAL_GPIO_WritePin( LED_Green_GPIO_Port,  LED_Green_Pin,  GPIO_PIN_RESET)	// ��LED����������
#define LED_GREEN_TOGGLE()	HAL_GPIO_TogglePin(LED_Green_GPIO_Port,  LED_Green_Pin)						// ���̊֐����ĂԂ��тɗ�LED�̓_���Ə�����؂�ւ���
#define LED_BLUE_ON()		HAL_GPIO_WritePin( LED_Blue_GPIO_Port, 	 LED_Blue_Pin,   GPIO_PIN_SET)		// ��LED��_������
#define LED_BLUE_OFF()		HAL_GPIO_WritePin( LED_Blue_GPIO_Port, 	 LED_Blue_Pin,   GPIO_PIN_RESET)	// ��LED����������
#define LED_BLUE_TOGGLE()	HAL_GPIO_TogglePin(LED_Blue_GPIO_Port, 	 LED_Blue_Pin)						// ���̊֐����ĂԂ��тɐ�LED�̓_���Ə�����؂�ւ���
#define LED_ALL_ON()		HAL_GPIO_WritePin(GPIOA, LED_Yellow_Pin|LED_Red_Pin|LED_Green_Pin|LED_Blue_Pin, GPIO_PIN_SET)	// �SLED��_������
#define LED_ALL_OFF()		HAL_GPIO_WritePin(GPIOA, LED_Yellow_Pin|LED_Red_Pin|LED_Green_Pin|LED_Blue_Pin, GPIO_PIN_RESET)	// �SLED����������
#define LED_ALL_TOGGLE()	HAL_GPIO_TogglePin(GPIOA, LED_Yellow_Pin|LED_Red_Pin|LED_Green_Pin|LED_Blue_Pin)				// �SLED�̓_���Ə�����؂�ւ���

/* �X�C�b�`�֐��Q */
#define SWITCH_ONOFF()		HAL_GPIO_ReadPin(Switch_GPIO_Port, Switch_Pin)				// �X�C�b�`���������ƃn�C���Ԃ��Ă���

/* UART�ʐM�֐��Q(communication.c) */
/* �����������ꂽsyscalls.c��Src�t�@�C���Ɉڂ��Astdio.h���C���N���[�h���邱�Ƃ�printf��scanf���g�p�\ */
void 		Communication_TerminalSend( uint8_t );		// 1�������M
uint8_t 	Communication_TerminalRecv( void );			// 1������M
void 		Communication_Initialize( void );			// printf��scanf���g�p���邽�߂̐ݒ�
void 		Communication_ClearScreen( void );			// ��ʃN���A&�J�[�\��������

/* ���[�^�֐��Q(motor.c) */
void 		Motor_Initialize( void );					// ���[�^�쓮�p�^�C�}�[�̊J�n
void 		Motor_StopPWM( void );						// ���[�^���~
void 		Motor_SetDuty_Left( int16_t );				// �����[�^���w�肵��Duty�ŉ�]������[0-1000]
void 		Motor_SetDuty_Right( int16_t );				// �E���[�^���w�肵��Duty�ŉ�]������[0-1000]

/* �G���R�[�_�֐��Q(encoder.c) */
void 		Encoder_Initialize( void );					// �G���R�[�_�p�^�C�}�[�̊J�n
void 		Encoder_ResetCount_Left( void );			// ���G���R�[�_�̃J�E���g�������l�ɂ���
void 		Encoder_ResetCount_Right( void );			// �E�G���R�[�_�̃J�E���g�������l�ɂ���
float 		Encoder_GetAngle_Left( void );				// ���^�C���̊p�x���擾����[rad]
float 		Encoder_GetAngle_Right( void );				// �E�^�C���̊p�x���擾����[rad]

/* �����Z���T�֐��Q(imu.c) */
uint8_t		IMU_CheckWHOAMI( void );					// �����Z���T�̓���m�F�֐�(0xe0���Ԃ��Ă���ΐ���)
void		IMU_Initialize( void );						// �����Z���T�̏����ݒ�
void 		IMU_ResetReference( void );					// �����Z���T�̃��t�@�����X��␳����
float 		IMU_GetAccel_X( void );						// X�������x�v�̉����x���擾����[m/s^2]
float 		IMU_GetGyro_Z( void );						// Z���W���C���̊p���x���擾����[rad/s]

/* �ԊO�Z���T�֐��Q(ir_sensor.c) */
void 		Sensor_Initialize( void );					// AD�ϊ��̏����ݒ�
void 		Sensor_StartADC( void );					// AD�ϊ����J�n����
void 		Sensor_StopADC( void );						// AD�ϊ����~����
uint16_t 	Sensor_GetBatteryValue( void );				// �d���d����AD�l���擾����
int16_t 	Sensor_GetValue( uint8_t );					// �ԊO�Z���T��LED�I���I�t�����l���擾����
														// 0:�O�E�A1:���E�A2:�����A3:�O��
/* �o�b�e���[�֐��Q(battery.c) */
float 		Battery_GetVoltage( void );					// �o�b�e���̓d�����擾����[V]
void 		Battery_LimiterVoltage( void );				// �o�b�e���̓d����3.2V�ȉ��ɂȂ�ƋN�����Ȃ��悤�ɐ�������

/* ���荞�݊֐��Q(interrupt.c) */
void 		Interrupt_Initialize( void );				// ���C���̊��荞�ݏ����̏����ݒ�
void 		Interrupt_Main( void );						// ���C���̊��荞�ݏ���������
uint16_t 	Interrupt_GetDuty( void );					// ���荞�ݏ������̌v�Z�������擾����
uint16_t 	Interrupt_GetDuty_Max( void );				// ���荞�ݏ������̍ő�v�Z�������擾����
float		Interrupt_GetBootTime( void );				// �}�C�R�����N�����Ă���o�߂������Ԃ��擾����[s]

/* ���W���[���e�X�g�֐��Q(module_test.c) */
void 		module_test( void );						// �S���W���[���̓���m�F�p�e�X�g�֐�

#endif /* INDEX_H_ */
