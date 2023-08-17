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

#define PCLK			(HAL_RCC_GetPCLK2Freq())
#define TIMER_COUNT		(__HAL_TIM_GET_COUNTER(&htim5))
#define TIMER_LOAD		(__HAL_TIM_GET_AUTORELOAD(&htim5))
#define TIMER_PSC		((&htim5)->Instance->PSC + 1)

volatile static uint32_t	interrupt_count_now;
volatile static uint32_t	interrupt_duty;
volatile static uint32_t	interrupt_duty_max = 0;
volatile static float		boot_time = 0.f;


/* ---------------------------------------------------------------
	1ms周期で割り込み処理関数
--------------------------------------------------------------- */
void Interrupt_Main( void )
{
	// ここにメインの割り込み処理を記述する

}

/* ---------------------------------------------------------------
	メイン割り込みの初期設定関数
--------------------------------------------------------------- */
void Interrupt_Initialize( void )
{
	HAL_TIM_Base_Start_IT( &htim5 );
}

/* ---------------------------------------------------------------
	割り込み前処理関数
--------------------------------------------------------------- */
void Interrupt_PreProcess( void )
{
	volatile static uint32_t	interrupt_count_old = 0;
	volatile static uint64_t	boot_time_count = 0;

	interrupt_count_now = TIMER_COUNT;
	boot_time_count += (uint16_t)(interrupt_count_now - interrupt_count_old);
	interrupt_count_old = interrupt_count_now;
	boot_time = (float)boot_time_count / (float)(PCLK / TIMER_PSC);
}

/* ---------------------------------------------------------------
	割り込み後処理関数
--------------------------------------------------------------- */
void Interrupt_PostProcess( void )
{
	interrupt_duty = MIN(TIMER_COUNT - interrupt_count_now,
						 TIMER_COUNT - interrupt_count_now + TIMER_LOAD) * 1000 / TIMER_LOAD;
	interrupt_duty_max = MAX( interrupt_duty_max, interrupt_duty );
}

/* ---------------------------------------------------------------
	割り込み周期に占める呼び出し位置までの処理時間の割合を取得する関数
--------------------------------------------------------------- */
uint16_t Interrupt_GetDuty( void )
{
	return interrupt_duty;
}

/* ---------------------------------------------------------------
	上記割合の最大値を取得する関数
--------------------------------------------------------------- */
uint16_t Interrupt_GetDuty_Max( void )
{
	return interrupt_duty_max;
}

/* ---------------------------------------------------------------
	マイコン起動時からの経過時間を取得する関数
--------------------------------------------------------------- */
float Interrupt_GetBootTime( void )
{
	return boot_time;
}
