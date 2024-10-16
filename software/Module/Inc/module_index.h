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

#ifndef INC_MODULE_INDEX_H_
#define INC_MODULE_INDEX_H_

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

/* 便利な定数群 */
#define G					(9.80665f)					// 重量加速度[m/s^2]
#define PI					(3.1415926f)				// 円周率
#define SQRT2				(1.41421356237f)			// ルート2
#define SQRT3				(1.73205080757f)			// ルート3
#define SQRT5				(2.2360679775f)				// ルート5
#define SQRT7				(2.64575131106f)			// ルート7
#define _ESC				(0x1b)						// エスケープシーケンス
#define _LF					(0x0a)						// 改行シーケンス
#define _CR					(0x0d)						// 復帰シーケンス

/* 便利なマクロ関数群 */
#define DEG2RAD(x)			(((x)/180.0f)*PI)			// 度数法からラジアンに変換
#define RAD2DEG(x)			(180.0f*((x)/PI))			// ラジアンから度数法に変換
#define SWAP(a, b) 			((a != b) && (a += b, b = a - b, a -= b))
#define ABS(x) 				((x) < 0 ? -(x) : (x))		// 絶対値
#define SIGN(x)				((x) < 0 ? -1 : 1)			// 符号
#define MAX(a, b) 			((a) > (b) ? (a) : (b))		// 2つのうち大きい方を返します
#define MIN(a, b) 			((a) < (b) ? (a) : (b))		// 2つのうち小さい方を返します
#define MAX3(a, b, c) 		((a) > (MAX(b, c)) ? (a) : (MAX(b, c)))
#define MIN3(a, b, c) 		((a) < (MIN(b, c)) ? (a) : (MIN(b, c)))

/* LED関数群 */
#define LED_YELLOW_ON()			HAL_GPIO_WritePin( LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET)		// 黄LEDを点灯する
#define LED_YELLOW_OFF()		HAL_GPIO_WritePin( LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET)	// 黄LEDを消灯する
#define LED_YELLOW_TOGGLE()		HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin)					// この関数を呼ぶたびに黄LEDの点灯と消灯を切り替える
#define LED_RED_ON()			HAL_GPIO_WritePin( LED_RED_GPIO_Port, 	 LED_RED_Pin, 	 GPIO_PIN_SET)		// 赤LEDを点灯する
#define LED_RED_OFF()			HAL_GPIO_WritePin( LED_RED_GPIO_Port, 	 LED_RED_Pin,    GPIO_PIN_RESET)	// 赤LEDを消灯する
#define LED_RED_TOGGLE()		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, 	 LED_RED_Pin)						// この関数を呼ぶたびに赤LEDの点灯と消灯を切り替える
#define LED_GREEN_ON()			HAL_GPIO_WritePin( LED_GREEN_GPIO_Port,  LED_GREEN_Pin,  GPIO_PIN_SET)		// 緑LEDを点灯する
#define LED_GREEN_OFF()			HAL_GPIO_WritePin( LED_GREEN_GPIO_Port,  LED_GREEN_Pin,  GPIO_PIN_RESET)	// 緑LEDを消灯する
#define LED_GREEN_TOGGLE()		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,  LED_GREEN_Pin)						// この関数を呼ぶたびに緑LEDの点灯と消灯を切り替える
#define LED_BLUE_ON()			HAL_GPIO_WritePin( LED_BLUE_GPIO_Port, 	 LED_BLUE_Pin,   GPIO_PIN_SET)		// 青LEDを点灯する
#define LED_BLUE_OFF()			HAL_GPIO_WritePin( LED_BLUE_GPIO_Port, 	 LED_BLUE_Pin,   GPIO_PIN_RESET)	// 青LEDを消灯する
#define LED_BLUE_TOGGLE()		HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, 	 LED_BLUE_Pin)						// この関数を呼ぶたびに青LEDの点灯と消灯を切り替える
#define LED_ALL_ON()			HAL_GPIO_WritePin (GPIOA, LED_YELLOW_Pin|LED_RED_Pin|LED_GREEN_Pin|LED_BLUE_Pin, GPIO_PIN_SET)		// 全LEDを点灯する
#define LED_ALL_OFF()			HAL_GPIO_WritePin (GPIOA, LED_YELLOW_Pin|LED_RED_Pin|LED_GREEN_Pin|LED_BLUE_Pin, GPIO_PIN_RESET)	// 全LEDを消灯する
#define LED_ALL_TOGGLE()		HAL_GPIO_TogglePin(GPIOA, LED_YELLOW_Pin|LED_RED_Pin|LED_GREEN_Pin|LED_BLUE_Pin)					// 全LEDの点灯と消灯を切り替える

/* UART通信関数群(communicate.c) */
/* 自動生成されたsyscalls.cをSrcファイルに移し、stdio.hをインクルードすることでprintfやscanfも使用可能 */
void	 	Communicate_Transmit1byte( uint8_t );	// 1文字送信
uint8_t 	Communicate_Receice1byte( void );		// 1文字受信
void 		Communicate_Initialize( void );			// printfとscanfを使用するための設定
void 		Communicate_ClearReceiveBuffer( void );	// 受信バッファの初期化

/* モータ関数群(motor.c) */
void 		Motor_Initialize( void );				// モータ駆動用タイマーの開始
void 		Motor_StopPWM( void );					// モータを停止
void 		Motor_SetDuty_Left( int16_t );			// 左モータを指定したDutyで回転させる[0-1000]
void 		Motor_SetDuty_Right( int16_t );			// 右モータを指定したDutyで回転させる[0-1000]

/* エンコーダ関数群(encoder.c) */
void 		Encoder_Initialize( void );				// エンコーダ用タイマーの開始
void 		Encoder_ResetCount_Left( void );		// 左エンコーダのカウントを初期値にする
void 		Encoder_ResetCount_Right( void );		// 右エンコーダのカウントを初期値にする
float 		Encoder_GetAngle_Left( void );			// 左タイヤの角度を取得する[rad]
float 		Encoder_GetAngle_Right( void );			// 右タイヤの角度を取得する[rad]
void 		Encoder_DebugPrintf( void );

/* 慣性センサ関数群(imu.c) */
uint8_t		IMU_CheckWHOAMI( void );				// 慣性センサの動作確認関数(0x47が返ってくれば正常)
void		IMU_Initialize( void );					// 慣性センサの初期設定
void 		IMU_ResetReference( void );				// 慣性センサのリファレンスを補正する
float 		IMU_GetAccel_X( void );					// X軸加速度計の加速度を取得する[m/s^2]
float 		IMU_GetGyro_Z( void );					// Z軸ジャイロの角速度を取得する[rad/s]
void 		IMU_DebugPrintf( void );

/* 赤外センサ関数群(ir_sensor.c) */
void 		Sensor_Initialize( void );				// AD変換の初期設定
void 		Sensor_TurnOffLED( void );				// 赤外センサのLEDを消灯する
void 		Sensor_TurnOnLED( void );				// 赤外センサのLEDを点灯する
uint16_t 	Sensor_GetBatteryValue( void );			// 電源電圧のAD値を取得する
int16_t 	Sensor_GetValue( uint8_t );				// 赤外センサのLEDオンオフ差分値を取得する
													// 0:横右、1:前右、2:横左、3:前左
void 		Sensor_DebugPrintf( void );

/* バッテリー関数群(battery.c) */
float 		Battery_GetVoltage( void );				// バッテリの電圧を取得する[V]
void 		Battery_LimiterVoltage( void );			// バッテリの電圧が3.2V以下になると起動しないように制限する

/* 割り込み関数群(interrupt.c) */
void 		Interrupt_Initialize( void );			// メインの割り込み処理の初期設定
void 		Interrupt_Main( void );					// メインの割り込み処理を書く
uint16_t 	Interrupt_GetDuty( void );				// 割り込み処理内の計算割合を取得する
uint16_t 	Interrupt_GetDuty_Max( void );			// 割り込み処理内の最大計算割合を取得する
float		Interrupt_GetBootTime( void );			// マイコンが起動してから経過した時間を取得する[s]

/* フラッシュ関数群(flash.c) */
uint8_t 	Flash_Clear( void );					// Flashのデータを消去
uint8_t* 	Flash_Load( void );						// Flashのデータを全てに読出し先頭アドレスを取得する
uint8_t 	Flash_Save( void );						// Flashにデータを書込む

/* モジュールテスト関数群(module_test.c) */
void 		module_test( void );					// 全モジュールの動作確認用テスト関数

/* シェル関数群(myshell.c) */
void 		Myshell_Initialize( void );				// NT-Shellの初期設定
void 		Myshell_Execute( void );				// NT-Shellの実行関数

#endif /* INC_MODULE_INDEX_H_ */
