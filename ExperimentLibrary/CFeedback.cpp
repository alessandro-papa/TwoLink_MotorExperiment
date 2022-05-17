#include "CFeedback.h"
#include "CTargetFileAccess.h"

CFeedback::CFeedback()  : mK(1, 2), mSOffset{0.0F}
{
	CTargetFileAccess file;
	file.readMatrixFromFile("/root/1_Config/1_Feedback/K.csv", mK);
}
const CExperimentData& CFeedback::calculate(const CExperimentData& expData)
{
	/* state vector */
	CVector x{2};
	x(0) = expData.mPhi;
	x(1) = expData.mPhiD;

	/* input vector */
	CVector u{1};
	u(0) = 0.0f;
	u 	 = - mK * x;

	/* resulting state vector of robot*/
	mX.mPhi 	= expData.mPhi;
	mX.mPhiD 	= expData.mPhiD;
	mX.mU 		= u(0);

	return mX;
}
const CExperimentData& CFeedback::getOutput() const
{
	return mX;
}
void CFeedback::reloadConfiguration()
{
	CTargetFileAccess file;
	file.readMatrixFromFile("/root/1_Config/1_Feedback/K.csv", mK);
}
void CFeedback::reset()
{

}
void CFeedback::setSOffset(float offset)
{
	mSOffset = offset;
}
