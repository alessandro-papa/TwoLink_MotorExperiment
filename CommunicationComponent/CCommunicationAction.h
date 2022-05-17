// Michael Meindl, 30.05.2019
#ifndef CCOMMUNICATIONACTION_H
#define CCOMMUNICATIONACTION_H
#include "CMessage.h"
#include "CReceiveTask.h"
#include "CServer.h"
#include "CThread.h"

class CCommunicationAction
{
public:
	void entryDisconnected();
	void exitDisconnected();
	void entryConnected();
	void exitConnected();

	void transmitExperimentData(const CMessage& msg);
public:
	CCommunicationAction();
	CCommunicationAction& operator=(const CCommunicationAction&) = delete;
	CCommunicationAction(const CCommunicationAction&)            = delete;
	~CCommunicationAction()                                      = default;
private:
	CServer      mServer;
	CReceiveTask mReceiveTask;
	CThread      mReceiveThread;
};

#endif
