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
#include <string.h>

#define FLASH_SECTOR_NUM     FLASH_SECTOR_1
#define FLASH_SECTOR_SIZE    1024*16

// Flashから読みだしたデータを退避するRAM上の領域
// 4byteごとにアクセスをするので、アドレスが4の倍数になるように配置する
static uint8_t work_ram[FLASH_SECTOR_SIZE] __attribute__ ((aligned(4)));

// Flashのsector1の先頭に配置される変数(ラベル)
// 配置と定義はリンカスクリプトで行う
extern char _flash_start;

/* ----------------------------------------------------------------------------------
	Flashのsector1を消去
-----------------------------------------------------------------------------------*/
uint8_t Flash_Clear( void )
{
	HAL_FLASH_Unlock();

	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.Sector = FLASH_SECTOR_NUM;
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.NbSectors = 1;

	// Eraseに失敗したsector番号がerror_sectorに入る
	// 正常にEraseができたときは0xFFFFFFFFが入る
	uint32_t error_sector;
	HAL_StatusTypeDef result = HAL_FLASHEx_Erase(&EraseInitStruct, &error_sector);

	HAL_FLASH_Lock();

	return result == HAL_OK && error_sector == 0xFFFFFFFF;
}

/* ----------------------------------------------------------------------------------
	Flashのsector1の内容を全てwork_ramに読み出す
	work_ramの先頭アドレスを返す
-----------------------------------------------------------------------------------*/
uint8_t* Flash_Load( void )
{
	memcpy(work_ram, &_flash_start, FLASH_SECTOR_SIZE);
	return work_ram;
}

/* ----------------------------------------------------------------------------------
	Flashのsector1を消去後、work_ramにあるデータを書き込む
-----------------------------------------------------------------------------------*/
uint8_t Flash_Save( void )
{
	// Flashをclear
	if( !Flash_Clear() ) return 0;

	uint32_t *p_work_ram = (uint32_t*)work_ram;

	HAL_FLASH_Unlock();

	// work_ramにあるデータを4バイトごとまとめて書き込む
	HAL_StatusTypeDef result;
	const size_t write_cnt = FLASH_SECTOR_SIZE / sizeof(uint32_t);

	for( size_t i=0; i<write_cnt; i++ ) {
		result = HAL_FLASH_Program(
			FLASH_TYPEPROGRAM_WORD,
			(uint32_t)(&_flash_start) + sizeof(uint32_t) * i,
			p_work_ram[i]
		);
		if( result != HAL_OK ) break;
	}

	HAL_FLASH_Lock();

	return result == HAL_OK;
}
