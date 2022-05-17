// Michael Meindl, 23.05.2019
#include "CProxy.h"

volatile CProxy* CProxy::sInstance{nullptr};
CMutex CProxy::sMutex{true, true};

CProxy& CProxy::getInstance()
{
	if(nullptr == sInstance)
	{
		if(sMutex.take(false))
		{
			if(nullptr == sInstance)
			{
				sInstance = new CProxy;
			}
		}
	}
	return *const_cast<CProxy*>(sInstance);
}
CProxy::CProxy() : mCommunicationComponentPtr{nullptr}, mExperimentComponentPtr{nullptr}
{

}
void CProxy::registerCommunicationComponent(AComponentBase* commComp)
{
	mCommunicationComponentPtr = commComp;
}
void CProxy::registerExperimentComponent(AComponentBase* controlComp)
{
	mExperimentComponentPtr = controlComp;
}
bool CProxy::timerTick(bool waitForever)
{
	return mExperimentComponentPtr->mQueue.push_back(CMessage{EEvent::TimerTick}, waitForever);
}
bool CProxy::clientConnected(bool waitForever)
{
	return mCommunicationComponentPtr->mQueue.push_back(CMessage{EEvent::ClientConnected}, waitForever);
}
bool CProxy::clientDisconnected(bool waitForever)
{
	auto ret{mExperimentComponentPtr->mQueue.push_back(CMessage{EEvent::StopExperiment}, waitForever)};
	return ret && mCommunicationComponentPtr->mQueue.push_back(CMessage{EEvent::ClientDisconnected}, waitForever);
}
bool CProxy::routeClientMessage(const CMessage& msg, bool waitForever)
{
	return mExperimentComponentPtr->mQueue.push_back(msg, waitForever);
}
bool CProxy::signalILCExperimentFinished(bool waitForever)
{
	CMessage msg{EEvent::ILCExperimentFinished};
	return mExperimentComponentPtr->mQueue.push_back(msg, waitForever);
}
bool CProxy::signalILCTrialFinished(bool waitForever)
{
	CMessage msg{EEvent::ILCTrialFinished};
	return mExperimentComponentPtr->mQueue.push_back(msg, waitForever);
}
bool CProxy::signalILCTrialFinishedSoftTransitionEnabled(bool waitForever)
{
	CMessage msg{EEvent::ILCTrialFinishedSoftTransitionEnabled};
	return mExperimentComponentPtr->mQueue.push_back(msg, waitForever);
}
bool CProxy::signalInSpeedControlArea(bool waitForever)
{
	CMessage msg{EEvent::InSpeedControlArea};
	return mExperimentComponentPtr->mQueue.push_back(msg, waitForever);
}
bool CProxy::signalEndOfIteration(bool waitForever)
{
	return mExperimentComponentPtr->mQueue.push_back(CMessage{EEvent::IterationFinished}, waitForever);
}
bool CProxy::signalSoftTransitionFinished(bool waitForever)
{
	CMessage msg{EEvent::SoftTransitionFinished};
	return mExperimentComponentPtr->mQueue.push_back(msg, waitForever);
}
