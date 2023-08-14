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

#define NUM_ADC				(12)
#define GET_ADC_DATA(x)		adc_value[x-1]

typedef enum {
	LED_FL_OFF 	= 5,
	LED_FL_ON 	= 6,
	LED_SL_OFF 	= 9,
	LED_SL_ON 	= 10,
	LED_SR_OFF 	= 7,
	LED_SR_ON 	= 8,
	LED_FR_OFF 	= 3,
	LED_FR_ON 	= 4,
} t_sensor_mode;

static uint32_t		led_on_pattern[]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};				// LED点灯コマンド
static uint32_t		led_off_pattern[] = {0x00F00000, 0x00F00000, 0x00F00000, 0x00F00000,
										 0x00F00000, 0x00F00000, 0x00F00000, 0x00F00000,
										 0x00F00000, 0x00F00000, 0x00F00000, 0x00F00000};	// LED消灯コマンド
static uint16_t		adc_value[NUM_ADC];		// AD変換値

// 割り込み内の処理を記述した関数群
extern void Interrupt_Main( void );
extern void Interrupt_PreProcess( void );
extern void Interrupt_PostProcess( void );

/* ---------------------------------------------------------------
	全AD変換終了後に行われる割り込み関数(Don't change the function name)
--------------------------------------------------------------- */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	Interrupt_PreProcess();
	Interrupt_Main();
	Interrupt_PostProcess();
}

/* ---------------------------------------------------------------
	赤外センサの出力設定関数
--------------------------------------------------------------- */
void Sensor_TurnOffLED( void )
{
	for( int8_t i = 0; i < NUM_ADC; i++ ) {
		led_on_pattern[i] = 0;
	}
}

void Sensor_TurnOnLED( void )
{
	Sensor_TurnOffLED();
	led_on_pattern[LED_FL_OFF] = LED_FL_Pin;
	led_on_pattern[LED_SL_OFF] = LED_SL_Pin;
	led_on_pattern[LED_SR_OFF] = LED_SR_Pin;
	led_on_pattern[LED_FR_OFF] = LED_FR_Pin;
}

/* ---------------------------------------------------------------
	赤外センサの初期設定関数
--------------------------------------------------------------- */
void Sensor_Initialize( void )
{
	htim1.Instance->DIER |= TIM_DIER_CC1DE | TIM_DIER_CC2DE;
	__HAL_TIM_MOE_ENABLE(&htim1);
	__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);

	Sensor_TurnOnLED();
	HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_CC1], (uint32_t)led_on_pattern,  (uint32_t)(&(GPIOA->BSRR)), NUM_ADC);
	HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_CC2], (uint32_t)led_off_pattern, (uint32_t)(&(GPIOA->BSRR)), NUM_ADC);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_value, NUM_ADC);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

/* ---------------------------------------------------------------
	AD変換を開始する関数
--------------------------------------------------------------- */
void Sensor_StartADC( void )
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

/* ---------------------------------------------------------------
	AD変換を停止する関数
--------------------------------------------------------------- */
void Sensor_StopADC( void )
{
	HAL_GPIO_WritePin(GPIOA, LED_FL_Pin|LED_SL_Pin|LED_SR_Pin|LED_FR_Pin, GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
}

/* ---------------------------------------------------------------
	バッテリのAD値を取得する関数
--------------------------------------------------------------- */
uint16_t Sensor_GetBatteryValue( void )
{
	return( (adc_value[0] + adc_value[1] + adc_value[10] + adc_value[11]) / 4 );
}

/* ---------------------------------------------------------------
	赤外センサの偏差値を取得する関数
--------------------------------------------------------------- */
int16_t Sensor_GetValue( uint8_t dir )
{
	switch( dir ) {
		case 3: 	return GET_ADC_DATA(LED_FL_ON) - GET_ADC_DATA(LED_FL_OFF);	break;
		case 2: 	return GET_ADC_DATA(LED_SL_ON) - GET_ADC_DATA(LED_SL_OFF);	break;
		case 0: 	return GET_ADC_DATA(LED_SR_ON) - GET_ADC_DATA(LED_SR_OFF);	break;
		case 1: 	return GET_ADC_DATA(LED_FR_ON) - GET_ADC_DATA(LED_FR_OFF);	break;
		default:	return -1;													break;
	}
}

/* ---------------------------------------------------------------
	デバッグ用
--------------------------------------------------------------- */
void Sensor_DebugPrintf( void )
{
	printf( "%5d (%4d - %3d), %5d (%4d - %3d), %5d (%4d - %3d), %5d (%4d - %3d)\r\n",
			GET_ADC_DATA(LED_FL_ON) - GET_ADC_DATA(LED_FL_OFF), GET_ADC_DATA(LED_FL_ON), GET_ADC_DATA(LED_FL_OFF),
			GET_ADC_DATA(LED_SL_ON) - GET_ADC_DATA(LED_SL_OFF), GET_ADC_DATA(LED_SL_ON), GET_ADC_DATA(LED_SL_OFF),
			GET_ADC_DATA(LED_SR_ON) - GET_ADC_DATA(LED_SR_OFF), GET_ADC_DATA(LED_SR_ON), GET_ADC_DATA(LED_SR_OFF),
			GET_ADC_DATA(LED_FR_ON) - GET_ADC_DATA(LED_FR_OFF), GET_ADC_DATA(LED_FR_ON), GET_ADC_DATA(LED_FR_OFF) );
}


