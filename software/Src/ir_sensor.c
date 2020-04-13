
#include "index.h"

#define NUM_ADC						(12)

#define SENSOR_ALL_OFF()			HAL_GPIO_WritePin(GPIOA, LED_FL_Pin|LED_SL_Pin|LED_SR_Pin|LED_FR_Pin, GPIO_PIN_RESET)
#define SENSOR_ALL_ON()				HAL_GPIO_WritePin(GPIOA, LED_FL_Pin|LED_SL_Pin|LED_SR_Pin|LED_FR_Pin, GPIO_PIN_SET)
#define SENSOR_FRONT_ON()			HAL_GPIO_WritePin(GPIOA, LED_FL_Pin|LED_FR_Pin, GPIO_PIN_SET)
#define SENSOR_FRONT_OFF()			HAL_GPIO_WritePin(GPIOA, LED_FL_Pin|LED_FR_Pin, GPIO_PIN_RESET)
#define SENSOR_SIDE_ON()			HAL_GPIO_WritePin(GPIOA, LED_SL_Pin|LED_SR_Pin, GPIO_PIN_SET)
#define SENSOR_SIDE_OFF()			HAL_GPIO_WritePin(GPIOA, LED_SL_Pin|LED_SR_Pin, GPIO_PIN_RESET)

#define	SENSOR_ALL_OFF_PATTERN		(0x0000)
#define	SENSOR_ALL_ON_PATTERN		(LED_FL_Pin|LED_SL_Pin|LED_SR_Pin|LED_FR_Pin)
#define	SENSOR_FRONT_ON_PATTERN 	(LED_FL_Pin|LED_FR_Pin)
#define	SENSOR_SIDE_ON_PATTERN		(LED_SL_Pin|LED_SR_Pin)

typedef enum {
	led_front_left_off 	= 5,
	led_front_left_on 	= 6,
	led_side_left_off 	= 9,
	led_side_left_on 	= 10,
	led_side_right_off 	= 7,
	led_side_right_on 	= 8,
	led_front_right_off = 3,
	led_front_right_on 	= 4,
} t_sensor_mode;

static uint32_t		sensor_on_pattern[]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// LED点灯コマンド
static uint32_t		sensor_off_pattern[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// LED消灯コマンド
static uint16_t		adc_value[NUM_ADC];		// AD変換値


/* ---------------------------------------------------------------
	赤外センサの初期設定関数
--------------------------------------------------------------- */
void Sensor_Initialize( void )
{
	htim1.Instance->DIER |= TIM_DIER_CC1DE | TIM_DIER_CC2DE;
//	htim1.Instance->CCER &= ~(TIM_CCER_CC3E);
//	htim1.Instance->CCER |= TIM_CCER_CC3E;
	__HAL_TIM_MOE_ENABLE(&htim1);
	//__HAL_TIM_ENABLE(&htim1);

//	HAL_DMA_RegisterCallback (htim1.hdma[TIM_DMA_ID_CC2], HAL_DMA_XFER_CPLT_CB_ID, TIM1_CC2_Callback);
	HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_CC1], (uint32_t)sensor_on_pattern,  (uint32_t)(&(GPIOA->ODR)), NUM_ADC);
	HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_CC2], (uint32_t)sensor_off_pattern, (uint32_t)(&(GPIOA->ODR)), NUM_ADC);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_value, NUM_ADC);

	Sensor_StartADC();
	__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_OC_Start_IT(&htim1, TIM_CHANNEL_3);
	//HAL_TIM_Base_Start_IT(&htim1);
}

/* ---------------------------------------------------------------
	赤外センサによる計測を開始する関数
--------------------------------------------------------------- */
void Sensor_StartADC( void )
{
	for( int8_t i = 0; i < NUM_ADC; i++ ) {
		sensor_on_pattern[i] = 0;
	}
	sensor_on_pattern[led_front_left_off]	= LED_FL_Pin;
	sensor_on_pattern[led_side_left_off]	= LED_SL_Pin;
	sensor_on_pattern[led_side_right_off]	= LED_SR_Pin;
	sensor_on_pattern[led_front_right_off]	= LED_FR_Pin;
}

/* ---------------------------------------------------------------
	赤外センサによる計測を停止する関数
--------------------------------------------------------------- */
void Sensor_StopADC( void )
{
	for( int8_t i = 0; i < NUM_ADC; i++ ) {
		sensor_on_pattern[i] = 0;
	}
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
/*	if( 0 <= dir || dir <= 3 ) {
		return sensor_value[dir].on - sensor_value[dir].off;
	} else {
		return -1;
	}
*/
	switch( dir ) {
		case 3: 	return adc_value[led_front_left_on-1]  - adc_value[led_front_left_off-1];	break;
		case 2: 	return adc_value[led_side_left_on-1]   - adc_value[led_side_left_off-1];	break;
		case 0: 	return adc_value[led_side_right_on-1]  - adc_value[led_side_right_off-1];	break;
		case 1: 	return adc_value[led_front_right_on-1] - adc_value[led_front_right_off-1];	break;
		default:	return -1;																	break;
	}
}

/* ---------------------------------------------------------------
	デバッグ用
--------------------------------------------------------------- */
void Sensor_DebugPrintf( void )
{
/*	printf( "%5d (%4d - %3d), %5d (%4d - %3d), %5d (%4d - %3d), %5d (%4d - %3d)\r\n",
			adc_value[led_front_left_on-1]  - adc_value[led_front_left_off-1],  adc_value[led_front_left_on-1],  adc_value[led_front_left_off-1],
			adc_value[led_side_left_on-1]   - adc_value[led_side_left_off-1],   adc_value[led_side_left_on-1],   adc_value[led_side_left_off-1],
			adc_value[led_side_right_on-1]  - adc_value[led_side_right_off-1],  adc_value[led_side_right_on-1],  adc_value[led_side_right_off-1],
			adc_value[led_front_right_on-1] - adc_value[led_front_right_off-1], adc_value[led_front_right_on-1], adc_value[led_front_right_off-1]);
*/
	printf("%5d, %5d, %5d, %5d, %5d, %5d, %5d, %5d, %5d, %5d, %5d, %5d\r\n",
			adc_value[0], adc_value[1], adc_value[2], adc_value[3], adc_value[4], adc_value[5],
			adc_value[6], adc_value[7], adc_value[8], adc_value[9], adc_value[10], adc_value[11]);
}
