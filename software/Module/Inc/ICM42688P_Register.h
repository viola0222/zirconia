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

#ifndef INC_ICM42688P_REGISTER_H_
#define INC_ICM42688P_REGISTER_H_

// USER BANK
#define REG_BANK_SEL			(118)
#define REG_USER_BANK_0 		(0)
#define REG_USER_BANK_1 		(1)
#define REG_USER_BANK_2 		(2)
#define REG_USER_BANK_3 		(3)
#define REG_USER_BANK_4 		(4)

// USER BANK0 REGISTER MAP
#define DEVICE_CONFIG			(17)
#define DRIVE_CONFIG			(19)
#define INT_CONFIG				(20)
#define FIFO_CONFIG				(22)
#define TEMP_DATA1				(29)
#define TEMP_DATA0				(30)
#define ACCEL_DATA_X1			(31)
#define ACCEL_DATA_X0			(32)
#define ACCEL_DATA_Y1			(33)
#define ACCEL_DATA_Y0			(34)
#define ACCEL_DATA_Z1			(35)
#define ACCEL_DATA_Z0			(36)
#define GYRO_DATA_X1			(37)
#define GYRO_DATA_X0			(38)
#define GYRO_DATA_Y1			(39)
#define GYRO_DATA_Y0			(40)
#define GYRO_DATA_Z1			(41)
#define GYRO_DATA_Z0			(42)
#define TMST_FSYNCH				(43)
#define TMST_FSYNCL				(44)
#define INT_STATUS				(45)
#define FIFO_COUNTH				(46)
#define FIFO_COUNTL				(47)
#define FIFO_DATA				(48)
#define APEX_DATA0				(49)
#define APEX_DATA1				(50)
#define APEX_DATA2				(51)
#define APEX_DATA3				(52)
#define APEX_DATA4				(53)
#define APEX_DATA5				(54)
#define INT_STATUS2				(55)
#define INT_STATUS3				(56)
#define SIGNAL_PATH_RESET		(75)
#define INTF_CONFIG0			(76)
#define INTF_CONFIG1			(77)
#define PWR_MGMT0				(78)
#define GYRO_CONFIG0			(79)
#define ACCEL_CONFIG0			(80)
#define GYRO_CONFIG1			(81)
#define GYRO_ACCEL_CONFIG0		(82)
#define ACCEL_CONFIG1			(83)
#define TMST_CONFIG				(84)
#define APEX_CONFIG0			(86)
#define SMD_CONFIG				(87)
#define FIFO_CONFIG1			(95)
#define FIFO_CONFIG2			(96)
#define FIFO_CONFIG3			(97)
#define FSYNC_CONFIG			(98)
#define INT_CONFIG0				(99)
#define INT_CONFIG1				(100)
#define INT_SOURCE0				(101)
#define INT_SOURCE1				(102)
#define INT_SOURCE3				(104)
#define INT_SOURCE4				(105)
#define FIFO_LOST_PKT0			(108)
#define FIFO_LOST_PKT1			(109)
#define SELF_TEST_CONFIG		(112)
#define WHO_AM_I				(117)

// USER BANK1 REGISTER MAP
#define SENSOR_CONFIG0			(3)
#define GYRO_CONFIG_STATIC2		(11)
#define GYRO_CONFIG_STATIC3		(12)
#define GYRO_CONFIG_STATIC4		(13)
#define GYRO_CONFIG_STATIC5		(14)
#define GYRO_CONFIG_STATIC6		(15)
#define GYRO_CONFIG_STATIC7		(16)
#define GYRO_CONFIG_STATIC8		(17)
#define GYRO_CONFIG_STATIC9		(18)
#define GYRO_CONFIG_STATIC10	(19)
#define XG_ST_DATA				(95)
#define YG_ST_DATA				(96)
#define ZG_ST_DATA				(97)
#define TMSTVAL0				(98)
#define TMSTVAL1				(99)
#define TMSTVAL2				(100)
#define INTF_CONFIG4			(122)
#define INTF_CONFIG5			(123)
#define INTF_CONFIG6			(124)

// USER BANK2 REGISTER MAP
#define ACCEL_CONFIG_STATIC2	(3)
#define ACCEL_CONFIG_STATIC3	(4)
#define ACCEL_CONFIG_STATIC4	(5)
#define XA_ST_DATA				(59)
#define YA_ST_DATA				(60)
#define ZA_ST_DATA				(61)

// USER BANK4 REGISTER MAP
#define APEX_CONFIG1			(64)
#define APEX_CONFIG2			(65)
#define APEX_CONFIG3			(66)
#define APEX_CONFIG4			(67)
#define APEX_CONFIG5			(68)
#define APEX_CONFIG6			(69)
#define APEX_CONFIG7			(70)
#define APEX_CONFIG8			(71)
#define APEX_CONFIG9			(72)
#define ACCEL_WOM_X_THR			(74)
#define ACCEL_WOM_Y_THR			(75)
#define ACCEL_WOM_Z_THR			(76)
#define INT_SOURCE6				(77)
#define INT_SOURCE7				(78)
#define INT_SOURCE8				(79)
#define INT_SOURCE9				(80)
#define INT_SOURCE10			(81)
#define OFFSET_USER0			(119)
#define OFFSET_USER1			(120)
#define OFFSET_USER2			(121)
#define OFFSET_USER3			(122)
#define OFFSET_USER4			(123)
#define OFFSET_USER5			(124)
#define OFFSET_USER6			(125)
#define OFFSET_USER7			(126)
#define OFFSET_USER8			(127)

#endif /* INC_ICM42688P_REGISTER_H_ */
