/*
 * TMotor.h
 *
 *  Created on: Sep 8, 2020
 *      Author: vmuser
 */

#ifndef HARDWARE_TMOTOR_H_
#define HARDWARE_TMOTOR_H_

#include "CPWM.h"
#include "CGPIO.h"

template<int maxCurrent, int torqueConstant, int gearRatio> 	// maxCurrent in [mA], torqueConstant in [mNm/mA] || [mNm/A]
class TMotor {
public:
	void enableMotor()
	{
		mEnablePin.setHigh();
	}
	void disableMotor()
	{
		mEnablePin.setLow();
		this->setTorque(0.0F);;
	}
	void setTorque(float torque)
	{
		torque >= 0 ? mDirectionPin.setLow() : mDirectionPin.setHigh(); // if torque >= 0.0 --> setLow(), else setHigh()
		torque = torque >= 0 ? torque : -torque;
		torque = torque > cMaxTorque ? cMaxTorque : torque;
		float pwm_value = 10.0F + 80.0F*( torque / cMaxTorque );
		mTorquePWM.setDutyCycle(pwm_value);
	}
public:
	TMotor(const std::string& pwmchipNr,
		   const std::string& pwmNr,
		   const std::string& enablePinNr,
		   const std::string& directionPinNr) : cMaxCurrent{maxCurrent / 1000.0F},						// convert from mA to A
//		   	   	   	   	   	   	   	   	   	    cTorqueConstant{torqueConstant / 1000.0F / 1000.0F}, 	// convert from mNm/mA to Nm/A
												cTorqueConstant{torqueConstant / 1000.0F}, 				// convert from mNm/A to Nm/A
												cGearRatio{gearRatio},
												mTorquePWM(pwmchipNr, pwmNr),
												mEnablePin(enablePinNr),
												mDirectionPin(directionPinNr)
	{
		mEnablePin.setLow();
		mTorquePWM.setDutyCycle(10.0F);
	}
	TMotor(const TMotor&) = delete;
	TMotor& operator=(const TMotor&) = delete;
	~TMotor() = default;
private:
	const float cMaxCurrent;
	const float cTorqueConstant;
	const float cGearRatio;
	const float cMaxTorque{cMaxCurrent * cTorqueConstant * cGearRatio};
	CPWM  mTorquePWM;
	CGPIO mEnablePin;
	CGPIO mDirectionPin;
};

#endif /* HARDWARE_TMOTOR_H_ */
