/**
 * Copyright 2020 kohiro
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "index.h"


/* ---------------------------------------------------------------
	各機能の動作確認用関数
--------------------------------------------------------------- */
void module_test( void )
{
	uint16_t	line 	  = 0;
	uint8_t		key;
	int16_t		duty_l	  = 0;
	int16_t		duty_r	  = 0;

	// DMAを一時的に停止
	HAL_DMA_Abort(huart1.hdmarx);

	// エンコーダのカウントをリセット
	Encoder_ResetCount_Left();
	Encoder_ResetCount_Right();

	while( 1 ) {
		// 割り込み処理率を表示
		printf("<Boot Time> %8.3f[s]\r\n", Interrupt_GetBootTime()); line++;
		printf("<Interrupt> %3.1f[%%] (MAX : %3.1f[%%])\r\n",
				(float)Interrupt_GetDuty()/10.f, (float)Interrupt_GetDuty_Max()/10.f); line++;

		// モータを指定のDutyを表示
		printf("<PWM Duty> L: %4.1f[%%],  R: %4.1f[%%]\r\n",
				(float)duty_l/10.f, (float)duty_r/10.f); line++;

		// エンコーダの角度表示
		printf("<Encoder> L: %5.1f[deg],  R: %5.1f[deg]\r\n",
				RAD2DEG(Encoder_GetAngle_Left()), RAD2DEG(Encoder_GetAngle_Right())); line++;

		// バッテリー電圧の表示
		printf("<Battery> %3.2f[V]\r\n", Battery_GetVoltage()); line++;

		// 壁センサのAD値表示
		printf("<IR Sensor> FL: %4d, SL: %4d SR: %4d, FR: %4d\r\n",
				Sensor_GetValue(3), Sensor_GetValue(2), Sensor_GetValue(1), Sensor_GetValue(0)); line++;

		// IMU（加速度計とジャイロ）の計測値表示
		printf("<IMU> Accel_X: %5.3f[m/s^2], Gyro_Z: %6.3f[rad/s]\r\n",
				IMU_GetAccel_X(), IMU_GetGyro_Z()); line++;

		// モータのDuty入力
		key = Communicate_TerminalRecv();
		switch( key ) {
			case '1': duty_l += 1;		break;
			case 'q': duty_l -= 1;		break;
			case '2': duty_l += 10;		break;
			case 'w': duty_l -= 10;		break;
			case '3': duty_l += 100;	break;
			case 'e': duty_l -= 100;	break;
			case '7': duty_r += 1;		break;
			case 'u': duty_r -= 1;		break;
			case '8': duty_r += 10;		break;
			case 'i': duty_r -= 10;		break;
			case '9': duty_r += 100;	break;
			case 'o': duty_r -= 100;	break;
			case 'r': // reset
				duty_l = duty_r = 0;
				break;
			case 0x1b: goto END; // [esc] exit
		}
		duty_l = SIGN(duty_l) * MIN( 950, ABS(duty_l) );
		duty_r = SIGN(duty_r) * MIN( 950, ABS(duty_r) );

		// モータを回転
		Motor_SetDuty_Left(duty_l);
		Motor_SetDuty_Right(duty_r);

		fflush(stdout);
		HAL_Delay(500);
		// 画面のクリア
		printf("%c[0J", 0x1b);
		printf("%c[%dA", 0x1b, line);
	}
	END:;
	Motor_StopPWM();
}

