
#include "index.h"

/* ---------------------------------------------------------------
	�e�@�\�̓���m�F�p�֐�
--------------------------------------------------------------- */
void module_test( void )
{
	uint16_t	line 	  = 0;
	uint8_t		key;
	int16_t		duty_l	  = 0;
	int16_t		duty_r	  = 0;

	// �G���R�[�_�̃J�E���g�����Z�b�g
	Encoder_ResetCount_Left();
	Encoder_ResetCount_Right();

	while( 1 ) {
		// ���荞�ݏ�������\��
		printf("<Boot Time> %8.3f[s]\r\n", Interrupt_GetBootTime()); line++;
		printf("<Interrupt> %3.1f[%%] (MAX : %3.1f[%%])\r\n",
				(float)Interrupt_GetDuty()/10.f, (float)Interrupt_GetDuty_Max()/10.f); line++;

		// ���[�^���w���Duty��\��
		printf("<PWM Duty> L: %4.1f[%%],  R: %4.1f[%%]\r\n",
				(float)duty_l/10.f, (float)duty_r/10.f); line++;

		// �G���R�[�_�̊p�x�\��
		printf("<Encoder> L: %5.1f[deg],  R: %5.1f[deg]\r\n",
				RAD2DEG(Encoder_GetAngle_Left()), RAD2DEG(Encoder_GetAngle_Right())); line++;

		// �o�b�e���[�d���̕\��
		printf("<Battery> %3.2f[V]\r\n", Battery_GetVoltage()); line++;

		// �ǃZ���T��AD�l�\��
		printf("<IR Sensor> FL: %4d, SL: %4d SR: %4d, FR: %4d\r\n",
				Sensor_GetValue(3), Sensor_GetValue(2), Sensor_GetValue(1), Sensor_GetValue(0)); line++;

		// IMU�i�����x�v�ƃW���C���j�̌v���l�\��
		printf("<IMU> Accel_X: %5.3f[m/s^2], Gyro_Z: %6.3f[rad/s]\r\n",
				IMU_GetAccel_X(), IMU_GetGyro_Z()); line++;

		// ���[�^��Duty����
		key = Communication_TerminalRecv();
		switch( key ) {
			case '1': duty_l += 1; 	 break;
			case 'q': duty_l -= 1; 	 break;
			case '2': duty_l += 10;  break;
			case 'w': duty_l -= 10;  break;
			case '3': duty_l += 100; break;
			case 'e': duty_l -= 100; break;
			case '7': duty_r += 1; 	 break;
			case 'u': duty_r -= 1; 	 break;
			case '8': duty_r += 10;  break;
			case 'i': duty_r -= 10;  break;
			case '9': duty_r += 100; break;
			case 'o': duty_r -= 100; break;
			case 'r': // reset
				duty_l = duty_r = 0;
				break;
			case 0x1b: goto END; // [esc] exit
		}
		Motor_SetDuty_Left(duty_l);
		Motor_SetDuty_Right(duty_r);

		fflush(stdout);
		HAL_Delay(500);
		// ��ʂ̃N���A
		printf("%c[0J", 0x1b);
		printf("%c[%dA", 0x1b, line);
	}
	END:;
	Motor_StopPWM();
}

