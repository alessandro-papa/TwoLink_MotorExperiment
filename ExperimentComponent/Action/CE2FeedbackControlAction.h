#ifndef CE2FEEDBACKCONTROLACTION_H
#define CE2FEEDBACKCONTROLACTION_H
#include "CExperimentActionBase.h"
#include "CStateEstimation.h"
#include "CFilter.h"
#include "CFeedback.h"
#include "TActionHolder.h"
#include "TLinHierarchy.h"

class CE2FeedbackControlAction : public CExperimentActionBase
{
public:
	void onEntryE2FeedbackControl();
	void onExitE2FeedbackControl();

	void enableFeedback();
	void disableFeedback();

	void enableIntegralFeedback();
	void disableIntegralFeedback();

	void reloadConfiguration();
	void resetMotors();

	void toggleOffset();

	void sampleFeedbackControl();

public:
	CE2FeedbackControlAction();
	CE2FeedbackControlAction& operator=(const CE2FeedbackControlAction&) = delete;
	CE2FeedbackControlAction(const CE2FeedbackControlAction&)            = delete;
	~CE2FeedbackControlAction()                                          = default;
private:
	/* hardware */
	CDynamixelServoSystem 		mServoSystem;
	/* control | signal flow | timing */
	TLinHierarchy< TActionHolder,
				   CStateEstimation,
				   CFilter,
				   CFeedback> mControl;
	float                     	mTime;
	bool    					mFeedbackFlag;
	/* testing experiment stuff */
	bool 						mFirstRun;
	float 						mOffsetTick{1.57f}; 	/* offset steps for step response */
	float 						mOffset;
	enum OffsetFSM{negative, zero, positive};
	OffsetFSM mOffsetFSM;
};

#endif
