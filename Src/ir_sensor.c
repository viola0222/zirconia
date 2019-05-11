
#include "index.h"

#define SENSOR_ALL_OFF()			HAL_GPIO_WritePin(GPIOA, LED_FL_Pin|LED_SL_Pin|LED_SR_Pin|LED_FR_Pin, GPIO_PIN_RESET)
#define SENSOR_FRONT_ON()			HAL_GPIO_WritePin(GPIOA, LED_FL_Pin|LED_FR_Pin, GPIO_PIN_SET)
#define SENSOR_FRONT_OFF()			HAL_GPIO_WritePin(GPIOA, LED_FL_Pin|LED_FR_Pin, GPIO_PIN_RESET)
#define SENSOR_SIDE_ON()			HAL_GPIO_WritePin(GPIOA, LED_SL_Pin|LED_SR_Pin, GPIO_PIN_SET)
#define SENSOR_SIDE_OFF()			HAL_GPIO_WritePin(GPIOA, LED_SL_Pin|LED_SR_Pin, GPIO_PIN_RESET)

#define	SENSOR_ALL_OFF_PATTERN		(0x0000)
#define	SENSOR_FRONT_ON_PATTERN 	(LED_FL_Pin|LED_FR_Pin)
#define	SENSOR_SIDE_ON_PATTERN		(LED_SL_Pin|LED_SR_Pin)

typedef enum {
	front_right = 0,
	side_right 	= 1,
	side_left	= 2,
	front_left	= 3,
} t_sensor_dir;

typedef enum {
	sensor_all_off_mode 	= 0,
	sensor_front_on_mode 	= 1,
	sensor_side_on_mode 	= 2,
} t_sensor_mode;

typedef struct {	//センサ情報用構造体
	uint16_t	off;		// LEDオフ時の値
	uint16_t	on;			// LEDオン時の値
} t_sensor_value;

static uint16_t		sensor_on_pattern;		// LED点灯コマンド
static uint16_t		sensor_off_pattern;		// LED消灯コマンド
static uint8_t		sensor_mode;			// センシングパターン

static uint16_t			adc_value[5];		// AD変換値
static uint16_t			battery_value;		// バッテリ電圧の生データ
static t_sensor_value	sensor_value[4];	// IRセンサの生データ


/* ---------------------------------------------------------------
	LED消灯時に次のセンシングパターンに切り替えるコールバック関数
--------------------------------------------------------------- */
void TIM1_CC2_Callback( DMA_HandleTypeDef* hdma )
{
	switch( sensor_mode ) {
		case sensor_all_off_mode:
			sensor_on_pattern = SENSOR_ALL_OFF_PATTERN;
		break;

		case sensor_front_on_mode:
			sensor_on_pattern = SENSOR_FRONT_ON_PATTERN;
		break;

		case sensor_side_on_mode:
			sensor_on_pattern = SENSOR_SIDE_ON_PATTERN;
		break;
	}
	// 次のLED点灯パターンに切替
	sensor_mode = (sensor_mode + 1) % 3;
}

/* ---------------------------------------------------------------
	AD変換完了後のコールバック関数
--------------------------------------------------------------- */
void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef* hadc )
{
	switch( sensor_mode ) {
		// LEDオフ時のセンサ値
		case sensor_all_off_mode:
			battery_value 					= adc_value[0];
			sensor_value[front_right].off 	= adc_value[1];
			sensor_value[side_right].off	= adc_value[2];
			sensor_value[side_left].off 	= adc_value[3];
			sensor_value[front_left].off 	= adc_value[4];
		break;

		// 前LEDオン時のセンサ値
		case sensor_front_on_mode:
			sensor_value[front_right].on 	= adc_value[1];
			sensor_value[front_left].on 	= adc_value[4];
		break;

		// 横LEDオン時のセンサ値
		case sensor_side_on_mode:
			sensor_value[side_right].on 	= adc_value[2];
			sensor_value[side_left].on 		= adc_value[3];
		break;
	}
}

/* ---------------------------------------------------------------
	赤外センサの初期設定関数
--------------------------------------------------------------- */
void Sensor_Initialize( void )
{
	HAL_DMA_RegisterCallback (htim1.hdma[TIM_DMA_ID_CC2], HAL_DMA_XFER_CPLT_CB_ID, TIM1_CC2_Callback);
	HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_CC1], (uint32_t)&sensor_on_pattern,  (uint32_t)(&(GPIOA->ODR)), 1);
	HAL_DMA_Start_IT(htim1.hdma[TIM_DMA_ID_CC2], (uint32_t)&sensor_off_pattern, (uint32_t)(&(GPIOA->ODR)), 1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_value, sizeof(adc_value)/sizeof(uint16_t));

	htim1.Instance->DIER |= TIM_DIER_CC1DE | TIM_DIER_CC2DE;
	__HAL_TIM_MOE_ENABLE(&htim1);

	Sensor_StartADC();
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

/* ---------------------------------------------------------------
	赤外センサによる計測を開始する関数
--------------------------------------------------------------- */
void Sensor_StartADC( void )
{
	sensor_on_pattern = SENSOR_ALL_OFF_PATTERN;
	sensor_mode = sensor_all_off_mode;

	__HAL_TIM_CLEAR_FLAG(&htim1, TIM_FLAG_UPDATE);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

/* ---------------------------------------------------------------
	赤外センサによる計測を停止する関数
--------------------------------------------------------------- */
void Sensor_StopADC( void )
{
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);

	SENSOR_ALL_OFF();
}

/* ---------------------------------------------------------------
	バッテリのAD値を取得する関数
--------------------------------------------------------------- */
uint16_t Sensor_GetBatteryValue( void )
{
	return( battery_value );
}

/* ---------------------------------------------------------------
	赤外センサの偏差値を取得する関数
--------------------------------------------------------------- */
int16_t Sensor_GetValue( uint8_t dir )
{
	if( 0 <= dir || dir <= 3 ) {
		return sensor_value[dir].on - sensor_value[dir].off;
	} else {
		return -1;
	}
}

/* ---------------------------------------------------------------
	デバッグ用
--------------------------------------------------------------- */
void Sensor_DebugPrintf( void )
{
	printf( "%5d (%4d - %3d), %5d (%4d - %3d), %5d (%4d - %3d), %5d (%4d - %3d)\r\n",
			sensor_value[3].on - sensor_value[3].off, sensor_value[3].on, sensor_value[3].off,
			sensor_value[2].on - sensor_value[2].off, sensor_value[2].on, sensor_value[2].off,
			sensor_value[1].on - sensor_value[1].off, sensor_value[1].on, sensor_value[1].off,
			sensor_value[0].on - sensor_value[0].off, sensor_value[0].on, sensor_value[0].off );

}
