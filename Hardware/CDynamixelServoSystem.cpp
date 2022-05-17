/*
 * CDynamixelServoSystem.cpp
 *
 *  Created on: 02.09.2021
 *      Author: sandr
 */

#include <CDynamixelServoSystem.h>
#include "CServoSystemData.h"
#include "Assertion.h"
#include <iostream>

CDynamixelServoSystem::CDynamixelServoSystem(UInt8 numberOfMotors) : mNumberOfMotors(numberOfMotors)
{
	/* needed by dynamixel SDK to control uart port */
	mPortHandler 	= dynamixel::PortHandler::getPortHandler(cUARTDevice);
	mPacketHandler  = dynamixel::PacketHandler::getPacketHandler(sProtocolVersion);

	/* open uart port on cUARTDevice */
	bool success = mPortHandler->openPort();
	std::string path  = cUARTDevice;
	sAssertion(success, "(CDynamixelServo::CDynamixelServo) Failed to open " + path, true);

	/* set baud rate on port */
	success = mPortHandler->setBaudRate(sBaudrate);
	sAssertion(success, "(CDynamixelServo::CDynamixelServo) Failed to set baud rate on " + path, true);

	/* init all motors */
//	for(UInt8 i = 1; i <= mNumberOfMotors; i++)
//	{
//		this->initMotor(i);
//	}
}

/*
 * method to initialize motor(ID)
 */
void CDynamixelServoSystem::initMotor(const UInt8 &ID)
{
	UInt8 dxl_error 	  = ERRNUM_RESULT_FAIL;

	/* disable torque to enable parameter configuration */
	Int16 dxl_comm_result = mPacketHandler->write1ByteTxRx(mPortHandler, ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
	dynamixelAssertion(dxl_comm_result, dxl_error, "CDynamixelServo", true);

	/* set operating mode to current control */
	dxl_comm_result = mPacketHandler->write1ByteTxRx(mPortHandler, ID, ADDR_OPERATING_MODE, OPERATING_MODE_CURRENT, &dxl_error);
	dynamixelAssertion(dxl_comm_result, dxl_error, "CDynamixelServo", true);

	/* set return delay time */
	dxl_comm_result = mPacketHandler->write1ByteTxRx(mPortHandler, ID, ADDR_RETURN_DELAY_TIME, RETURN_DELAY_TIME_20us, &dxl_error);
	dynamixelAssertion(dxl_comm_result, dxl_error, "CDynamixelServo", true);
}

bool CDynamixelServoSystem::fetchValues(CServoSystemData &servoSystemData)
{
	bool retVal = true;
	for(int i = 1; i<= mNumberOfMotors; i++)
	{
		retVal = retVal && this->getPosition(i, servoSystemData.mServoData[i].mPosition);
		retVal = retVal && this->getSpeed(i, servoSystemData.mServoData[i].mSpeed);
	}
	return retVal;
}

/*
 * method to enable motor(sID) & status LED
 */
bool CDynamixelServoSystem::enableMotor()
{
	return this->enableMotor(sID);
}

/*
 * method to enable motor(ID) & status LED
 */
bool CDynamixelServoSystem::enableMotor(const float &ID)
{
	/* enable torque and turn LED on */
	UInt8 dxl_error 	  = ERRNUM_RESULT_FAIL;
	mPacketHandler->write1ByteTxRx(mPortHandler, ID, ADDR_LED, LED_ON, &dxl_error);
	Int16 dxl_comm_result = mPacketHandler->write1ByteTxRx(mPortHandler, ID, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);

	return dynamixelAssertion(dxl_comm_result, dxl_error, "enableMotor", false);
}

/*
 * method to disable motor(sID) & status LED
 */
bool CDynamixelServoSystem::disableMotor()
{
	return this->disableMotor(sID);
}

/*
 * method to disable motor(ID) & status LED
 */
bool CDynamixelServoSystem::disableMotor(const float &ID)
{
	/* disable torque and turn LED off */
	UInt8 dxl_error		  = ERRNUM_RESULT_FAIL;
	mPacketHandler->write1ByteTxRx(mPortHandler, ID, ADDR_LED, LED_OFF, &dxl_error);
	Int16 dxl_comm_result = mPacketHandler->write1ByteTxRx(mPortHandler, ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);

	return dynamixelAssertion(dxl_comm_result, dxl_error, "disableMotor", false);
}

/*
 * method to get current position of motor(sID) [rad]
 */
bool CDynamixelServoSystem::getPosition(float &position)
{
	return this->getPosition(sID, position);
}

/*
 * method to get current position of motor(ID) [rad]
 */
bool CDynamixelServoSystem::getPosition(const float &ID, float &position)
{
	/* get current position raw value [64 bit 2K] */
	UInt8 dxl_error 		= ERRNUM_RESULT_FAIL;
	UInt64 pos_raw 			= 0;
	Int16 dxl_comm_result 	= mPacketHandler->read4ByteTxRx(mPortHandler, ID, ADDR_PRESENT_POSITION, (UInt32*)&pos_raw, &dxl_error);

	/* calc in radiant */
	// TODO try switch case
	if(pos_raw < sMaxPositivePosition_raw)
	/* positive position value */
	{
		float poly = 1 / sBitsPerRev * sRev2Rad;
		position   = pos_raw * poly; 				/* [rad] */
	}
	else if(pos_raw > sMaxPositivePosition_raw)
	/* negative position, different calculation */
	{
		Int64 pos_tmp 	= pos_raw - sMaxPosition_raw;
		position 		= pos_tmp / sBitsPerRev * sRev2Rad; 	/* [rad] */
	}
	else
	{
		std::cout << "[*] CDynamixelServoSystem::getPosition(): corrupted value for pos_raw! " << std::endl;
	}
	return dynamixelAssertion(dxl_comm_result, dxl_error, "getPosition", false);
}

/*
 * method to get current speed of motor(sID) [rad/sec]
 */
bool CDynamixelServoSystem::getSpeed(float &speed)
{
	return this->getSpeed(sID, speed);
}

/*
 * method to get current speed of motor(ID) [rad/sec]
 */
bool CDynamixelServoSystem::getSpeed(const float &ID, float &speed)
{
	/* get current speed raw value [32 bit 2K] */
	UInt8 dxl_error 		= ERRNUM_RESULT_FAIL;
	Int32 speed_raw 		= 0;
	Int16 dxl_comm_result 	= mPacketHandler->read4ByteTxRx(mPortHandler, ID, ADDR_PRESENT_VELOCITY, (UInt32*)&speed_raw, &dxl_error);

	/* conversion polynom */
	float poly 				= sMaxSpeed / sMaxSpeed_raw;	/* [rad / sec / Bit] */
	/* calc speed_raw into rad/sec */
	speed 					= speed_raw * poly; 			/* [rad / sec] */

	return dynamixelAssertion(dxl_comm_result, dxl_error, "getSpeed", false);
}

/*
 * method to set motor(sID) torque in [Nm]
 */
bool CDynamixelServoSystem::setTorque(const float &torque)
{
	return this->setTorque(sID, torque);
}

/*
 * method to set torque @ motor(ID) [Nm]
 */
bool CDynamixelServoSystem::setTorque(const float &ID, const float &torque)
{
	/* calc current from torque */
	float current = torque / sTorqueConstant; 	/* [A] */
	/* current saturation [A] */
	if(current < -sMaxCurrent)
	{
		current = -sMaxCurrent;
	}
	else if(current > sMaxCurrent)
	{
		current = sMaxCurrent;
	}
	/* calc current in 12 bit 2K */
	float poly 			= sMaxCurrent_raw / sMaxCurrent;
	Int16 current_raw   = current * poly;

	/* drive motor */
	UInt8 dxl_error 		= ERRNUM_RESULT_FAIL;
	Int16 dxl_comm_result 	= mPacketHandler->write2ByteTxRx(mPortHandler, ID, ADDR_GOAL_CURRENT, current_raw, &dxl_error);

	return dynamixelAssertion(dxl_comm_result, dxl_error, "setTorque", false);
}

/*
 * custom assertion to check serial communication
 */
bool CDynamixelServoSystem::dynamixelAssertion(const Int16 &dxl_comm_result, const UInt8 &dxl_error_result, std::string function, bool exitFlag)
{
	std::string comm_msg 	= "(CDynamixelServo::" + function + ") motor" + std::to_string(sID) + ": Failed communication. Dynamixel communication result: " + std::to_string(dxl_comm_result);
	std::string error_msg 	= "(CDynamixelServo::" + function + ") motor" + std::to_string(sID) + ": Failed to execute command. Dynamixel error result: " + std::to_string(dxl_error_result);

	bool retValComm 	= sAssertion((dxl_comm_result == COMM_SUCCESS), comm_msg, false);
	bool retValError 	= sAssertion((dxl_error_result == ERRNUM_NO_ERROR), error_msg, exitFlag);
	return retValComm && retValError;
}
