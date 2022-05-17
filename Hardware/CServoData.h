/*
 * CDynamixelData.h
 *
 *  Created on: Jan 18, 2022
 *      Author: vmuser
 */

#ifndef CSERVODATA_H_
#define CSERVODATA_H_

class CServoData
{
public:
	CServoData();
	CServoData& operator=(const CServoData&) 	= default;
	CServoData(const CServoData&)         		= default;
	~CServoData()                             		= default;
public:
	float mPosition;	/* [radiant] */
	float mSpeed;		/* [rad/sec] */
	float mTorque;		/* [Nm] */
};


#endif /* CSERVODATA_H_ */
