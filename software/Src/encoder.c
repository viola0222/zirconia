
#include "index.h"

#define ENC_CNT_L		(TIM2 -> CNT)
#define ENC_CNT_R		(TIM3 -> CNT)

#define ENC_ZERO		(20000)			/* エンコーダの初期値 */
#define ENC_RESOLUTION 	(1024 - 1)		/* エンコーダの分解能 */

/* ---------------------------------------------------------------
	位相係数モードのタイマーを開始する関数
--------------------------------------------------------------- */
void Encoder_Initialize( void )
{
	HAL_TIM_Encoder_Start( &htim2, TIM_CHANNEL_ALL );
	HAL_TIM_Encoder_Start( &htim3, TIM_CHANNEL_ALL );
}

/* ---------------------------------------------------------------
	左タイヤの位相係数カウントを初期化する関数
--------------------------------------------------------------- */
void Encoder_ResetCount_Left( void )
{
	ENC_CNT_L = ENC_ZERO;
}

/* ---------------------------------------------------------------
	右タイヤの位相係数カウントを初期化する関数
--------------------------------------------------------------- */
void Encoder_ResetCount_Right( void )
{
	ENC_CNT_R = ENC_ZERO;
}

/* ---------------------------------------------------------------
	左タイヤの角度を取得する関数[rad]
--------------------------------------------------------------- */
float Encoder_GetAngle_Left( void )
{
	return(2 * PI * (float)( (int32_t)ENC_CNT_L - (int32_t)ENC_ZERO ) / (float)ENC_RESOLUTION);
}

/* ---------------------------------------------------------------
	右タイヤの角度を取得する関数[rad]
--------------------------------------------------------------- */
float Encoder_GetAngle_Right( void )
{
	return(2 * PI * (float)( (int32_t)ENC_ZERO - (int32_t)ENC_CNT_R ) / (float)ENC_RESOLUTION);
}
