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

#define BATTERY_REFERENCE	(3.0f)
#define BATTERY_LIMIT		(3.2f)


/* ---------------------------------------------------------------
	バッテリの電圧を取得する関数
--------------------------------------------------------------- */
float Battery_GetVoltage( void )
{
	return (BATTERY_REFERENCE * (20.f / 10.f) * (float)Sensor_GetBatteryValue()) / 4096.f;
}

/* ---------------------------------------------------------------
	バッテリの電圧制限関数
--------------------------------------------------------------- */
void Battery_LimiterVoltage( void )
{
	volatile int	i;
	volatile float	battery_voltage_average;

	for( i = 0; i < 10; i++) {
		HAL_Delay(10);
		battery_voltage_average += Battery_GetVoltage();
	}
	battery_voltage_average /= 10;

	if( battery_voltage_average < BATTERY_LIMIT ) {
		while( 1 ) {
			LED_ALL_TOGGLE();
			HAL_Delay(200);
		}
	} else;
}
