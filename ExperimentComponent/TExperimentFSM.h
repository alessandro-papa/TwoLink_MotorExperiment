#ifndef TEXPERIMENTFSM_H
#define TEXPERIMENTFSM_H
#include "TLinHierarchy.h"
#include "TStateHolder.h"
#include "CExperimentAction.h"

template<class... StateList>
class TExperimentFSM : public AState
{
public:
	bool dispatch(CMessage& msg)                    override;
	bool tryEntry(CMessage& msg, AState*& statePtr) override;
	void onEntry()                                  override;
	void onExit()                                   override;
	bool onStandby(CMessage& msg);
public:
	TExperimentFSM();
	TExperimentFSM& operator=(const TExperimentFSM&) 	= delete;
	TExperimentFSM(const TExperimentFSM&)            	= delete;
	~TExperimentFSM()                             		= default;
private:
	AState*                                   mStatePtr;
	TLinHierarchy<TStateHolder, StateList...> mStateList;
	CExperimentAction                         mAction;
};

template<class... StateList>
TExperimentFSM<StateList...>::TExperimentFSM() : mStatePtr{nullptr}
{

}
template<class... StateList>
bool TExperimentFSM<StateList...>::onStandby(CMessage& msg)
{
	auto consumed = this->tryEntry(msg, mStatePtr);
	if(consumed == true)
	{
		mAction.exitStandby();
		mStatePtr->onEntry();
	}
	return consumed;
}
template<class... StateList>
bool TExperimentFSM<StateList...>::dispatch(CMessage& msg)
{
	auto consumed{false};
	if(mStatePtr == nullptr)
	{
		consumed = this->onStandby(msg);
	}
	else
	{
		consumed = mStatePtr->dispatch(msg);
	}

	if(consumed == false)
	{
		auto event = msg.getEvent();
		if(mStatePtr != nullptr)
		{
			if( (EEvent::StopExperiment == event) ||
				(EEvent::ClientDisconnected == event) )
			{
				mStatePtr->onExit();
				mStatePtr = nullptr;
				mAction.entryStandby();
			}
		}
	}

	while(sQueueSize > 0)
	{
		auto internalMessage{sInternalQueue};
		sQueueSize = 0U;
		consumed   = mStatePtr->dispatch(internalMessage);
	}

	return consumed;
}

template<class... StateList>
bool TExperimentFSM<StateList...>::tryEntry(CMessage& msg, AState*& statePtr)
{
	return mStateList.tryEntry(msg, statePtr);
}
template<class... StateList>
void TExperimentFSM<StateList...>::onEntry()
{

}
template<class... StateList>
void TExperimentFSM<StateList...>::onExit()
{

}

#endif
