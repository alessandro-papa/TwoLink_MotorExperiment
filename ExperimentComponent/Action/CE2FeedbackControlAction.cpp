#include "CE2FeedbackControlAction.h"
#include "ExperimentConfiguration.h"
#include "CServoSystemData.h"
#include <iostream>
using namespace std;

CE2FeedbackControlAction::CE2FeedbackControlAction() : mServoSystem{sNumberOfMotors}, mTime{0.0F}, mFeedbackFlag{false}, mFirstRun{true}, mOffset{0.0f}, mOffsetFSM{zero}
{

}
void CE2FeedbackControlAction::onEntryE2FeedbackControl()
{
	cout << "[*] Experiment-Component: Entering E2/Feedback-Control . . ." << endl;
	mTime         = 0.0F;
	mFeedbackFlag = false;
	mServoSystem.setTorque(0.0f);
	mServoSystem.enableMotor();
	sTimerTask.setPeriodMS(cFeedbackSamplePeriodMS);
	sTimerTask.resume(true);
}
void CE2FeedbackControlAction::onExitE2FeedbackControl()
{
	cout << "[*] Experiment-Component: Exiting E2/Feedback-Control . . . " << endl;
	mServoSystem.setTorque(0.0f);
	mServoSystem.disableMotor();
	sTimerTask.pause(true);
}
void CE2FeedbackControlAction::enableFeedback()
{
	cout << "[*] Experiment-Component: Enabling Feedback . . . " << endl;
	mFeedbackFlag = true;
}
void CE2FeedbackControlAction::disableFeedback()
{
	cout << "[*] Experiment-Component: Disabling Feedback . . . " << endl;
	mFeedbackFlag = false;
}
void CE2FeedbackControlAction::enableIntegralFeedback()
{
	cout << "[*] Experiment-Component: Enabling Integral-Feedback . . . " << endl;
	mControl.reset();
}
void CE2FeedbackControlAction::disableIntegralFeedback()
{
	cout << "[*] Experiment-Component: Disabling Integral-Feedback . . . " << endl;
}

void CE2FeedbackControlAction::reloadConfiguration()
{
	cout << "[*] Experiment-Component: Reloading Configuration . . . " << endl;
	mControl.reloadConfiguration();
	mControl.reset();
}
void CE2FeedbackControlAction::resetMotors()
{
	cout << "[*] Experiment-Component: Resetting Motors . . ." << endl;
	mServoSystem.disableMotor();
	mServoSystem.enableMotor();
}
void CE2FeedbackControlAction::toggleOffset()
{
	switch (mOffsetFSM)
	{
		case zero:
			mOffset 	= -mOffsetTick;
			mOffsetFSM 	= negative;
			break;
		case negative:
			mOffset 	= mOffsetTick;
			mOffsetFSM 	= positive;
			break;
		case positive:
			mOffset = 0.0f;
			mOffsetFSM = zero;
			break;
		default:
			cout << "[*] Experiment-Component: toggleOffset() corrpted Offset FSM . . . " << endl;
			break;
	}
}

void CE2FeedbackControlAction::sampleFeedbackControl()
{
	CServoSystemData servoSystemData;
	if(mServoSystem.fetchValues(servoSystemData))
	{
		servoSystemData.mServoData[1].mPosition += mOffset;
		mControl.calculate(servoSystemData);
		CExperimentData expData{mControl.CFeedback::getOutput()};

		/* control motors */
		if(mFeedbackFlag == true)
		{
			mServoSystem.setTorque(expData.mU);
		}
		else
		{
			mServoSystem.setTorque(0.0f);
		}
		expData.mTime = mTime;
		sProxy.transmitExperimentData(expData, false);
	}
	mTime += cFeedbackSamplePeriod;
}
