/**
 * @file	CControlActionBase.cpp
 * @author	Michael Meindl
 * @date	5.1.2017
 * @brief	Method defitions for CControlActionBase.
 */
#include "CExperimentActionBase.h"

// TODO remove CDynamixelServoSystem when tested
//CDynamixelServoSystem CExperimentActionBase::sServoSystem(sNumberOfMotors);
CTimerTask CExperimentActionBase::sTimerTask;
CThread	   CExperimentActionBase::sTimerThread(&CExperimentActionBase::sTimerTask,
										        CThread::PRIORITY_NORM);
CProxy&    CExperimentActionBase::sProxy = CProxy::getInstance();
