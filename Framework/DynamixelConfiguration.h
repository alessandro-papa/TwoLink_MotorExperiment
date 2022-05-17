/*
 * DynamixelConfiguration.h
 * container class which holds information and makros to read and write dynamixel motor's registers
 * for information about dynamixel SDK, see:	Project/DynamixelSDK/readme.txt
 *  Created on: 02.09.2021
 *      Author: sandr
 */

#include "Global.h"
#ifndef DYNAMIXELCONFIGURATION_H_
#define DYNAMIXELCONFIGURATION_H_

// number of motors in servo system
static constexpr UInt8 sNumberOfMotors = 1U;

// general variables
static constexpr float sPi = 3.14F;

// DYNAMIXEL error status values
static constexpr UInt8 ERRNUM_NO_ERROR 		= 0U;
static constexpr UInt8 ERRNUM_RESULT_FAIL 	= 1U;
static constexpr UInt8 ERRNUM_INSTRUCTION 	= 2U;
static constexpr UInt8 ERRNUM_CRC 			= 3U;
static constexpr UInt8 ERRNUM_DATA_RANGE 	= 4U;
static constexpr UInt8 ERRNUM_DATA_LENGTH 	= 5U;
static constexpr UInt8 ERRNUM_DATA_LIMIT 	= 6U;
static constexpr UInt8 ERRNUM_ACCESS 		= 7U;

// DYNAMIXEL XM430-W210-R register addresses
static constexpr UInt8 ADDR_BAUDRATE 			= 8U;		/* 1 byte */
static constexpr UInt8 ADDR_RETURN_DELAY_TIME 	= 9U; 		/* 1 byte */
static constexpr UInt8 ADDR_OPERATING_MODE 		= 11U; 		/* 1 byte */
static constexpr UInt8 ADDR_TORQUE_ENABLE 		= 64U;		/* 1 byte */
static constexpr UInt8 ADDR_LED 				= 65U;		/* 1 byte */
static constexpr UInt8 ADDR_GOAL_CURRENT 		= 102U;  	/* 2 byte */
static constexpr UInt8 ADDR_GOAL_POSITION 		= 116U;		/* 4 byte */
static constexpr UInt8 ADDR_PRESENT_CURRENT 	= 126U; 	/* 2 byte */
static constexpr UInt8 ADDR_PRESENT_VELOCITY 	= 128U; 	/* 4 byte */
static constexpr UInt8 ADDR_PRESENT_POSITION 	= 132U; 	/* 4 byte */

// DYNAMIXEL XM430-W210-R constant values
static constexpr float  PROTOCOL 			  	= 2.0F;
static constexpr UInt8 MINIMUM_POSITION_LIMIT 	= 0U;  			// Refer to the Minimum Position Limit of product eManual
static constexpr UInt16 MAXIMUM_POSITION_LIMIT 	= 4095U;  		// Refer to the Maximum Position Limit of product eManual
static constexpr UInt8 RETURN_DELAY_TIME_20us 	= 10U;			/* 10 * 2 [us] = 20[us], see manual */
static constexpr UInt8 RETURN_DELAY_TIME_100us 	= 50U;
static constexpr UInt8 ID1 						= 1U;
static constexpr UInt8 ID2 						= 2U;
static constexpr UInt8 OPERATING_MODE_CURRENT 	= 0U;
static constexpr UInt8 LED_ON 					= 1U;
static constexpr UInt8 LED_OFF 					= 0U;
static constexpr UInt8 TORQUE_ENABLE			= 1U;
static constexpr UInt8 TORQUE_DISABLE			= 0U;

#endif /* DYNAMIXELCONFIGURATION_H_ */
