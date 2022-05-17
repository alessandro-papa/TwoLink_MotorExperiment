#include "CE2FeedbackControl.h"

CE2FeedbackControl::CE2FeedbackControl()
{

}
bool CE2FeedbackControl::dispatch(CMessage& msg)
{
	auto event{msg.getEvent()};
	if(EEvent::Init == event)
	{
		mAction.onEntryE2FeedbackControl();
		return true;
	}
	if(EEvent::Exit == event)
	{
		mAction.onExitE2FeedbackControl();
		return true;
	}
	if(EEvent::EnableController == event)
	{
		mAction.enableFeedback();
		return true;
	}
	if(EEvent::DisableController == event)
	{
		mAction.disableFeedback();
		return true;
	}
	if(EEvent::TimerTick == event)
	{
		mAction.sampleFeedbackControl();
		return true;
	}
	if(EEvent::ReloadConfiguration == event)
	{
		mAction.reloadConfiguration();
		return true;
	}
	if(EEvent::EnableIntegralFeedback == event)
	{
		mAction.enableIntegralFeedback();
		return true;
	}
	if(EEvent::DisableIntegralFeedback == event)
	{
		mAction.disableIntegralFeedback();
		return false;
	}
	if(EEvent::ToggleOffset == event)
	{
		mAction.toggleOffset();
		return false;
	}

	return false;
}
bool CE2FeedbackControl::tryEntry(CMessage& msg, AState*& statePtr)
{
	auto event{msg.getEvent()};
	if(EEvent::RunE2FeedbackControl == event)
	{
		statePtr = this;
		return true;
	}
	return false;
}
void CE2FeedbackControl::onEntry()
{
	CMessage msg{EEvent::Init};
	this->dispatch(msg);
}
void CE2FeedbackControl::onExit()
{
	CMessage msg{EEvent::Exit};
	this->dispatch(msg);
}
