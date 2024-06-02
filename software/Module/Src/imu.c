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

#include "module_index.h"
#include "ICM42688P_Register.h"

#define REFFERENCE_NUM		(1000)		// 何回の平均をもってジャイロのリファレンス電圧とするか

// ジャイロ関連マクロ
#define GYRO_Z_SIGN			(1.f)		// ジャイロの出力の符号（自分の座標系に合った方向に、1.0fか－1.0fを掛けて修正する）
#define GYRO_Z_SENSITIVITY	(16.4f)

// 加速度計関連マクロ
#define ACCEL_X_SIGN		(1.f)		// 加速度計の出力の符号（自分の座標系に合った方向に、1.0fか－1.0fを掛けて修正する）
#define ACCEL_X_SENSITIVITY	(4096.f)

// ローカル関数宣言
void 	IMU_Write1byte( uint8_t , uint8_t );
uint8_t IMU_Read1byte( uint8_t );

// グローバル変数宣言
volatile static uint8_t imu_address = ACCEL_DATA_X1 | 0x80;
volatile static uint8_t	imu_value[13];			// value[0]はダミーデータ

volatile static int16_t	accel_x_value;			// X軸加速度計の生データ
volatile static int16_t	accel_x_reference;		// X軸加速度計のリファレンス

volatile static int16_t	gyro_z_value;			// Z軸ジャイロの生データ
volatile static int16_t	gyro_z_reference;		// Z軸ジャイロのリファレンス

/* ---------------------------------------------------------------
	IMUに1byte書き込む関数
--------------------------------------------------------------- */
void IMU_Write1byte( uint8_t addr , uint8_t data )
{
	uint8_t address = addr & 0x7f;

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &address, 1, 1);
	HAL_SPI_Transmit(&hspi2, &data, 1, 1);
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
}

/* ---------------------------------------------------------------
	IMUから1byte読み出す関数
--------------------------------------------------------------- */
uint8_t IMU_Read1byte( uint8_t addr )
{
	// 送信バッファに書き込み //
	uint8_t address = addr | 0x80;
	uint8_t value;

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &address, 1, 1);
	HAL_SPI_Receive(&hspi2, &value, 1, 1);
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	return value;
}

/* ---------------------------------------------------------------
	IMUの動作確認関数（WHO_AM_I(0x47)を取得する）
--------------------------------------------------------------- */
uint8_t IMU_CheckWHOAMI( void )
{
	return IMU_Read1byte( WHO_AM_I );
}

/* ---------------------------------------------------------------
	ICM42688Pの初期設定用関数
--------------------------------------------------------------- */
void IMU_Initialize( void )
{
	IMU_Write1byte(REG_BANK_SEL, REG_USER_BANK_0);	// バンクの切り替え
	HAL_Delay(100);

	IMU_Write1byte(PWR_MGMT0, 0x0F);	// 加速度計とジャイロを起動
	HAL_Delay(100);

	// ジャイロの設定
	IMU_Write1byte(GYRO_CONFIG0, 0x04);		// ジャイロのスケールを±2000deg/sに設定
	HAL_Delay(1);							// ジャイロのODRを4kHzに設定
	// 加速度計の設定
	IMU_Write1byte(ACCEL_CONFIG0, 0x26);	// 加速度計のスケールを±8gに設定
	HAL_Delay(1);							// 加速度計のODRを1kHzに設定
	// LPFの設定
	IMU_Write1byte(GYRO_ACCEL_CONFIG0, 0x71);	// 加速度計のLPFをODR/40に設定
	HAL_Delay(1);								// ジャイロのLPFをODR/4に設定

	// DMAの開始
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive_DMA( &hspi2, (uint8_t*)(&imu_address), (uint8_t*)imu_value, sizeof(imu_value)/sizeof(uint8_t) );
}

/* ---------------------------------------------------------------
	DMA送受信完了後のコールバック関数
--------------------------------------------------------------- */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef* hspi)
{
	HAL_GPIO_WritePin( SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET );

	accel_x_value = ( ((int16_t)imu_value[ 1]<<8) | ((int16_t)imu_value[ 2]&0x00ff) );
	gyro_z_value =  ( ((int16_t)imu_value[11]<<8) | ((int16_t)imu_value[12]&0x00ff) );

	HAL_GPIO_WritePin( SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET );
	HAL_SPI_TransmitReceive_DMA( &hspi2, (uint8_t*)(&imu_address), (uint8_t*)imu_value, sizeof(imu_value)/sizeof(uint8_t) );
}

/* ---------------------------------------------------------------
	IMUのリファレンスを補正する関数
--------------------------------------------------------------- */
void IMU_ResetReference( void )
{
	int16_t i;

	for(i = 0; i < REFFERENCE_NUM; i++) {
		HAL_Delay(1);
		accel_x_reference += accel_x_value;
		gyro_z_reference += gyro_z_value;
	}
	accel_x_reference /= REFFERENCE_NUM;
	gyro_z_reference /= REFFERENCE_NUM;
}

/* ---------------------------------------------------------------
	X軸加速度計の加速度を取得する関数[m/s^2]
--------------------------------------------------------------- */
float IMU_GetAccel_X( void )
{
	return ACCEL_X_SIGN * G * (accel_x_value - accel_x_reference) / ACCEL_X_SENSITIVITY;
}

/* ---------------------------------------------------------------
	Z軸ジャイロの角速度を取得する関数[rad/s]
--------------------------------------------------------------- */
float IMU_GetGyro_Z( void )
{
	return GYRO_Z_SIGN * DEG2RAD( (gyro_z_value - gyro_z_reference) / GYRO_Z_SENSITIVITY );
}

/* ---------------------------------------------------------------
	デバッグ用
--------------------------------------------------------------- */
void IMU_DebugPrintf( void )
{
	while( Communicate_Receice1byte() != _ESC ) {
		printf("%5d, %5d, %6.3f\t| %5d, %5d, %9.3f\r\n",
				accel_x_value, accel_x_reference, IMU_GetAccel_X(),
				gyro_z_value,  gyro_z_reference,  IMU_GetGyro_Z());
		HAL_Delay(100);
	}
}
