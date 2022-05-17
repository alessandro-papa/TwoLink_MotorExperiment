// Michael Meindl, 30.05.2019
#include "CCommunicationFSM.h"

CCommunicationFSM::CCommunicationFSM() : mState{sInitial}, mInternalQueue{}, mQueueSize{0}
{

}
bool CCommunicationFSM::dispatch(CMessage& msg)
{
	// call current state's action via method-pointer, parameter msg
	// see static constexpr to understand
	auto consumed{(this->*mState)(msg)};

	// while messages are available in internal queue, dispatch all of them
	while(mQueueSize != 0)
	{
		CMessage internalMessage{mInternalQueue};
		mQueueSize = 0;
		consumed = (this->*mState)(internalMessage);
	}

	// return if operations were successful
	return consumed;
}
bool CCommunicationFSM::onInitial(CMessage& msg)
{
	auto event{msg.getEvent()};		// auto type. here = event
	switch(event)
	{
	case EEvent::Init:
	{
		mState = sDisconnected;
		mAction.entryDisconnected();
		return true;
	}
	default:
		return false;
	}
}
bool CCommunicationFSM::onDisconnected(CMessage& msg)
{
	auto event{msg.getEvent()};
	switch(event)
	{
	case EEvent::Exit:
	{
		mAction.exitDisconnected();
		mState = sInitial;
		return true;
	}
	case EEvent::ClientConnected:
	{
		mAction.exitDisconnected();
		mState = sConnected;
		mAction.entryConnected();
		return true;
	}
	default:
		return false;
	}
}
bool CCommunicationFSM::onConnected(CMessage& msg)
{
	auto event{msg.getEvent()};
	switch(event)
	{
	case EEvent::Exit:
	{
		mAction.exitConnected();
		mState = sInitial;
		return true;
	}
	case EEvent::ClientDisconnected:
	{
		mAction.exitConnected();
		mState = sDisconnected;
		mAction.entryDisconnected();
		return true;
	}
	case EEvent::ExperimentData:
	{
		mAction.transmitExperimentData(msg);
		return true;
	}
	default:
		return false;
	}
}
