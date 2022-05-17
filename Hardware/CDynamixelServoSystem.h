/*
 * CDynamixelServo.h
 *
 *  Created on: 02.09.2021
 *      Author: sandr
 *      @brief: class to control one dynamixel servo motor by using BBBs UART1 interface
 */

#ifndef CDYNAMIXELSERVOSYSTEM_H_
#define CDYNAMIXELSERVOSYSTEM_H_

#include <CServoSystemData.h>
#include <string>
#include "DynamixelConfiguration.h"
#include "dynamixel_sdk.h"

class CDynamixelServoSystem
{
public:
	CDynamixelServoSystem(UInt8 numberOfMotors);
	CDynamixelServoSystem() 										= delete;
	CDynamixelServoSystem(const CDynamixelServoSystem&) 			= delete;
	CDynamixelServoSystem& operator=(const CDynamixelServoSystem&) 	= delete;
	~CDynamixelServoSystem() 										= default;

public:
	void initMotor(const UInt8 &ID);

	bool fetchValues(CServoSystemData &servoSystemData);

	bool enableMotor();
	bool enableMotor(const float &ID);

	bool disableMotor();
	bool disableMotor(const float &ID);

	bool setTorque(const float &torque);
	bool setTorque(const float &ID, const float &torque);

	bool getPosition(float &position);
	bool getPosition(const float &ID, float &position);

	bool getSpeed(float &speed);
	bool getSpeed(const float &ID, float &speed);

private:
	bool dynamixelAssertion(const Int16 &dxl_comm_result, const UInt8 &dxl_error_result, std::string function, bool exitFlag);

private:
	/* UART specific member */
	const char cUARTDevice[12]{"/dev/ttyS4"};
	static constexpr float sBaudrate{3000000.0F};
	static constexpr float sProtocolVersion{2.0F};
	dynamixel::PortHandler *mPortHandler;
	dynamixel::PacketHandler *mPacketHandler;

private:
	/* math stuff */
	static constexpr float sDeg2Rad{1.0F / 2.0F / sPi};
	static constexpr float sRev2Rad{2.0F * sPi};
	static constexpr float sRPM2RadPerSec{2.0F*sPi/60.0F};

private:
	/* servo system's state */
	CServoSystemData mServoSystemState;
	/* motor specific member */
	UInt8 mNumberOfMotors;
	static constexpr UInt8 sID{1U};										/* standard ID, motor1 */

	/* position stuff */
	static constexpr float sBitsPerRev{4096.0F};						/* bits per rev, see datasheet */
	static constexpr UInt64 sMaxPosition_raw{4294967295U};				/* max value position register 64 Bit */
	static constexpr UInt64 sMaxPositivePosition_raw{2147483647U};		/* max. positive position value in register */

	/* speed stuff */
	static constexpr float sMaxSpeedRPM{36.0F};						/* motor max speed [rpm], see datasheet */
	static constexpr float sMaxSpeed{sMaxSpeedRPM*sRPM2RadPerSec}; 	/* motor max speed [rad / sec] */
	static constexpr UInt32 sMaxSpeed_raw{170U};					/* motor max speed [Bit], see dynamixel wizard */

	/* torque stuff */
	static constexpr float sMaxTorque{8.1F}; 						/* [Nm], see datasheet  */
	static constexpr float sMaxCurrent{4.3F};						/* [A], see datasheet */
	static constexpr float sTorqueConstant{sMaxTorque/sMaxCurrent};	/* [Nm / A], see datasheet  */
	static constexpr float sMaxCurrent_raw{2047.0F};				/* [Bit], see dynamixel wizard, 12 Bit 2K */
};

#endif /* CDYNAMIXELSERVOSYSTEM_H_ */
