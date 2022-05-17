#include "CStateEstimation.h"
#include <cmath>
#include "math.h"

CStateEstimation::CStateEstimation() : mFirstRun{true}, mTheta0{0.0F}, mPrevious_SRel{0.0f}, mPrevious_Alpha{0.0f}
{

}
const CExperimentData& CStateEstimation::calculate(const CServoSystemData& input)
{
	mOutput.mPhi 	= input.mServoData[1].mPosition;
	mOutput.mPhiD 	= input.mServoData[1].mSpeed;

	return mOutput;
}
const CExperimentData& CStateEstimation::getOutput() const
{
	return mOutput;
}
void CStateEstimation::reset()
{
	mFirstRun = true;
}
void CStateEstimation::reloadConfiguration()
{

}
