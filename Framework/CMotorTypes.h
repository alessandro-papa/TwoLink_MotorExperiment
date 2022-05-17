/*
 * CMotorTypes.h
 *
 *  Created on: Sep 8, 2020
 *      Author: vmuser
 */

#ifndef HARDWARE_CMOTORTYPES_H_
#define HARDWARE_CMOTORTYPES_H_
#include "TMotor.h"

using EC60Flat_200W_48V = TMotor<8850, 113, 1>;			// 8850 mA, 113 mNm/A
using EC90Flat_600W_48V = TMotor<13000 , 231, 1>;		// 13000 mA, 231 mNm/mA


#endif /* HARDWARE_CMOTORTYPES_H_ */
