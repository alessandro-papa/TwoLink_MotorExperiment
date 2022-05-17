/*
 * CServoSystemData.h
 *
 *  Created on: Jan 18, 2022
 *      Author: vmuser
 */

#ifndef CSERVOSYSTEMDATA_H_
#define CSERVOSYSTEMDATA_H_
#include "CServoData.h"
#include "DynamixelConfiguration.h"

class CServoSystemData
{
public:
	CServoSystemData();
	CServoSystemData& operator=(const CServoSystemData&) 	= default;
	CServoSystemData(const CServoSystemData&)         		= default;
	~CServoSystemData()                             		= default;
public:
	CServoData mServoData[sNumberOfMotors];
};



#endif /* HARDWARE_CSERVOSYSTEMDATA_H_ */
