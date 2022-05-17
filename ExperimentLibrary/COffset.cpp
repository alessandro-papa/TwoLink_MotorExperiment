#include "COffset.h"

COffset::COffset() : mSOffset{0.0F}
{

}
const CExperimentData& COffset::calculate(const CExperimentData& input)
{
	mOutput     = input;
//	mOutput.mS += mSOffset;
	return mOutput;
}
const CExperimentData& COffset::getOutput() const
{
	return mOutput;
}
void COffset::reset()
{
	mSOffset = 0.0F;
}
void COffset::reloadConfiguration()
{

}
void COffset::setSOffset(const float& offset)
{
	mSOffset = offset;
}
