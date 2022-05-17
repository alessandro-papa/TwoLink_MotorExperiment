#ifndef CPROXY_H
#define CPROXY_H
#include "CMessage.h"
#include "CMutex.h"
#include "AComponentBase.h"

class CProxy
{
public:
	static CProxy& getInstance();
	void registerCommunicationComponent(AComponentBase* commComponent);
	void registerExperimentComponent(AComponentBase* controlComponent);

	bool timerTick(bool waitForever);
	template<class DataType>
	bool transmitExperimentData(const DataType& data, bool waitForever);

	bool clientDisconnected(bool waitForever);
	bool clientConnected(bool waitForever);
	bool routeClientMessage(const CMessage& msg, bool waitForever);

	bool signalILCExperimentFinished(bool waitForever);
	bool signalILCTrialFinished(bool waitForever);
	bool signalILCTrialFinishedSoftTransitionEnabled(bool waitForever);
	bool signalInSpeedControlArea(bool waitForever);
	bool signalEndOfIteration(bool waitForever);
	bool signalSoftTransitionFinished(bool waitForever);
private:
	CProxy();
	CProxy& operator=(const CProxy&) = delete;
	CProxy(const CProxy&)            = delete;
	~CProxy()                        = default;
private:
	static volatile CProxy* sInstance;
	static CMutex           sMutex;
	AComponentBase*         mCommunicationComponentPtr;
	AComponentBase*         mExperimentComponentPtr;
};

template<class DataType>
bool CProxy::transmitExperimentData(const DataType& data, bool waitForever)
{
	CMessage msg{EEvent::ExperimentData};
	msg.setData(data);

	return mCommunicationComponentPtr->mQueue.push_back(msg, waitForever);
}

#endif
