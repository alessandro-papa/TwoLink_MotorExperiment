#include "CFilter.h"
#include "math.h"

CFilter::CFilter() : mFirstRun{true}
{

}
const CExperimentData& CFilter::calculate(const CExperimentData& input)
{
	mOutput = input;

	return mOutput;
}
const CExperimentData& CFilter::getOutput() const
{
	return mOutput;
}
void CFilter::reset()
{
	mFirstRun 		  = true;
}
void CFilter::reloadConfiguration()
{

}
void CFilter::enableIntegralFeedback()
{

}
void CFilter::disableIntegralFeedback()
{

}

