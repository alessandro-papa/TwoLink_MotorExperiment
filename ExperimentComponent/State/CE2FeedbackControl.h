#ifndef CE2FEEDBACKCONTROL_H
#define CE2FEEDBACKCONTROL_H
#include "AState.h"
#include "CE2FeedbackControlAction.h"

class CE2FeedbackControl : public AState
{
public:
	bool dispatch(CMessage&)                    override;
	bool tryEntry(CMessage&, AState*& statePtr) override;
	void onEntry()                              override;
	void onExit()                               override;
public:
	CE2FeedbackControl();
	CE2FeedbackControl& operator=(const CE2FeedbackControl&) = delete;
	CE2FeedbackControl(const CE2FeedbackControl&)            = delete;
	~CE2FeedbackControl()                                    = default;
private:
	CE2FeedbackControlAction mAction;
};

#endif
