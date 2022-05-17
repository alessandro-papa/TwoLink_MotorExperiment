/**
 * @file	CControlActionBase.h
 * @author	Michael Meindl
 * @date	5.1.2017
 * @brief	Class definition for the basic Control-Actionhandler.
 */
#ifndef CEXPERIMENTACTIONBASE_H
#define CEXPERIMENTACTIONBASE_H
#include "CTimerTask.h"
#include "CThread.h"
#include "CProxy.h"
#include "CDynamixelServoSystem.h"

class CExperimentActionBase
{
public:
	CExperimentActionBase()                                        = default;
	CExperimentActionBase(const CExperimentActionBase&)            = delete;
	CExperimentActionBase& operator=(const CExperimentActionBase&) = delete;
	~CExperimentActionBase()                                       = default;
protected:
	// TODO remove CDynamixelServoSystem when tested
//	static CDynamixelServoSystem sServoSystem;
	static CTimerTask sTimerTask;
	static CThread    sTimerThread;
	static CProxy&    sProxy;
};

#endif
