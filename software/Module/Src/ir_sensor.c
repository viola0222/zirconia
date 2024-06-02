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

typedef enum {
	BATTERY_0	= 0,
	BATTERY_1	= 1,
	LED_FR_OFF 	= 2,
	LED_FR_ON 	= 3,
	LED_FL_OFF 	= 4,
	LED_FL_ON 	= 5,
	LED_SR_OFF 	= 6,
	LED_SR_ON 	= 7,
	LED_SL_OFF 	= 8,
	LED_SL_ON 	= 9,
	BATTERY_2	= 10,
	BATTERY_3	= 11,
	NUM_ADC,
} t_sensor_mode;

volatile static uint32_t	led_on_pattern[NUM_ADC] = {0};	// LED点灯コマンド
volatile static uint32_t	led_off_pattern = 0x000F0000;	// LED消灯コマンド
volatile static uint16_t	adc_value[NUM_ADC];				// AD変換値

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
	led_on_pattern[LED_FL_ON] = LED_FL_Pin;
	led_on_pattern[LED_SL_ON] = LED_SL_Pin;
	led_on_pattern[LED_SR_ON] = LED_SR_Pin;
	led_on_pattern[LED_FR_ON] = LED_FR_Pin;
}

/* ---------------------------------------------------------------
	赤外センサの初期設定関数
--------------------------------------------------------------- */
void Sensor_Initialize( void )
{
	htim1.Instance->DIER |= TIM_DIER_CC1DE | TIM_DIER_CC2DE;
	__HAL_TIM_MOE_ENABLE(&htim1);
	__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);

	HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_CC1], (uint32_t)led_on_pattern, (uint32_t)(&(GPIOA->BSRR)), NUM_ADC);
	HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_CC2], (uint32_t)(&led_off_pattern), (uint32_t)(&(GPIOA->BSRR)), 1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_value, NUM_ADC);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

/* ---------------------------------------------------------------
	バッテリのAD値を取得する関数
--------------------------------------------------------------- */
uint16_t Sensor_GetBatteryValue( void )
{
	return( (adc_value[BATTERY_0] + adc_value[BATTERY_1] + adc_value[BATTERY_2] + adc_value[BATTERY_3]) / 4 );
}

/* ---------------------------------------------------------------
	赤外センサの偏差値を取得する関数
--------------------------------------------------------------- */
int16_t Sensor_GetValue( uint8_t dir )
{
	switch( dir ) {
		case 3: 	return adc_value[LED_FL_ON] - adc_value[LED_FL_OFF];	break;
		case 2: 	return adc_value[LED_SL_ON] - adc_value[LED_SL_OFF];	break;
		case 0: 	return adc_value[LED_SR_ON] - adc_value[LED_SR_OFF];	break;
		case 1: 	return adc_value[LED_FR_ON] - adc_value[LED_FR_OFF];	break;
		default:	return -1;												break;
	}
}

/* ---------------------------------------------------------------
	デバッグ用
--------------------------------------------------------------- */
void Sensor_DebugPrintf( void )
{
	Sensor_TurnOnLED();
	while( Communicate_Receice1byte() != _ESC ) {
		printf( "%5d (%4d - %3d), %5d (%4d - %3d), %5d (%4d - %3d), %5d (%4d - %3d)\r\n",
				adc_value[LED_FL_ON] - adc_value[LED_FL_OFF], adc_value[LED_FL_ON], adc_value[LED_FL_OFF],
				adc_value[LED_SL_ON] - adc_value[LED_SL_OFF], adc_value[LED_SL_ON], adc_value[LED_SL_OFF],
				adc_value[LED_SR_ON] - adc_value[LED_SR_OFF], adc_value[LED_SR_ON], adc_value[LED_SR_OFF],
				adc_value[LED_FR_ON] - adc_value[LED_FR_OFF], adc_value[LED_FR_ON], adc_value[LED_FR_OFF] );

/*		printf("%5d", adc_value[0]);
		for(uint8_t i = 1; i < sizeof(adc_value) / sizeof(adc_value[0]); i++) {
			printf(" ,%5d", adc_value[i]);
		}
		printf("\r\n");
*/		HAL_Delay(100);
	}
	Sensor_TurnOffLED();
}


