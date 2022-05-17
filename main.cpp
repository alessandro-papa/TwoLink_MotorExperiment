/*
 *	TwoLink_MotorExperiment_V1: 	run feedback experiment of single two-link
 *
 *									run with TwoLink_Desktop_Application_V1
 *
 */

#include "CCommunicationComponent.h"
#include "CExperimentComponent.h"
#include "CThread.h"
#include "CProxy.h"
#include "FrameworkConfiguration.h"
#include "CDynamixelServoSystem.h"

int main()
{
	CExperimentComponent    experimentComponent;
	CCommunicationComponent communicationComponent;

	CProxy::getInstance().registerCommunicationComponent(&communicationComponent);
	CProxy::getInstance().registerExperimentComponent(&experimentComponent);

	CThread experimentThread(&experimentComponent, CThread::PRIORITY_NORM);
	CThread communicationThread(&communicationComponent, CThread::PRIORITY_NORM);

	experimentThread.start();
	communicationThread.start();

	experimentThread.join();
	communicationThread.join();

	return 0;
}
