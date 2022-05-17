#include "CExperimentComponent.h"
#include "CProxy.h"
#include <iostream>
#include <unistd.h>

CExperimentComponent::CExperimentComponent()
{

}
void CExperimentComponent::init()
{
	std::cout << "[*] Experiment-Component: Initializing . . ." << std::endl;
}
void CExperimentComponent::run()
{
	std::cout << "[*] Experiment-Component: Running . . ." << std::endl;

	CMessage msg;

	while(true)
	{
		if(mQueue.pop_front(msg, true))
		{
			mFSM.dispatch(msg);
		}
	}
}
