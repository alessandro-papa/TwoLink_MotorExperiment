// Michael Meindl, 30.05.2019
#include "CCommunicationAction.h"
#include "FrameworkConfiguration.h"
#include <iostream>
using namespace std;

CCommunicationAction::CCommunicationAction() : mServer{},
		                         mReceiveTask{mServer},
								 mReceiveThread{&mReceiveTask, CThread::PRIORITY_NORM}
{
	mReceiveThread.start();
}
void CCommunicationAction::entryDisconnected()
{
	cout << "[*] Communication-Component: Entering Disconnected" << endl;
}
void CCommunicationAction::exitDisconnected()
{
	cout << "[*] Communication-Component: Exiting Disconnected" << endl;
}
void CCommunicationAction::entryConnected()
{
	cout << "[*] Communication-Component: Entering Connected" << endl;
}
void CCommunicationAction::exitConnected()
{
	cout << "[*] Communication-Component: Exiting Connected" << endl;
}
void CCommunicationAction::transmitExperimentData(const CMessage& msg)
{
	mServer.transmitMessage(msg);
}
