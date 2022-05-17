#include "CExperimentAction.h"
#include <iostream>

CExperimentAction::CExperimentAction()
{
	sTimerThread.start();
}
void CExperimentAction::entryStandby()
{
	std::cout << "[*] Experiment-Component: Entering Standby . . . " << std::endl;
}
void CExperimentAction::exitStandby()
{
	std::cout << "[*] Experiment-Component: Exiting Standby . . . " << std::endl;
}
