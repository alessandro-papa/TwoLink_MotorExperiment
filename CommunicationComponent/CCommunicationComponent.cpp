#include <CCommunicationComponent.h>
#include <iostream>
#include <unistd.h>
#include "CMessage.h"

CCommunicationComponent::CCommunicationComponent()
{
	CMessage initMessage{EEvent::Init};
	mFSM.dispatch(initMessage);
}
void CCommunicationComponent::init()
{
	std::cout << "[*] Communication-Component: Initializing . . ." << std::endl;
}
void CCommunicationComponent::run()
{
	std::cout << "[*] Communication-Component: Running . . ." << std::endl;

	CMessage msg;
	while(mQueue.pop_front(msg, true))
	{
		mFSM.dispatch(msg);
	}
}
