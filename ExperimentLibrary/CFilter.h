#ifndef CFILTER_H
#define CFILTER_H
#include "CExperimentData.h"
#include "ExperimentConfiguration.h"
#include "CServoSystemData.h"

class CFilter
{
public:
	using InputType  = CExperimentData;
	using OutputType = CExperimentData;
public:
	const CExperimentData& calculate(const CExperimentData&);
	const CExperimentData& getOutput() const;
	void reset();
	void reloadConfiguration();
	void enableIntegralFeedback();
	void disableIntegralFeedback();
public:
	CFilter();
	CFilter& operator=(const CFilter&) = delete;
	CFilter(const CFilter&)            = delete;
	~CFilter()                         = default;
private:
	CExperimentData mOutput;
	bool       mFirstRun;

	static constexpr float sT{cFilterSamplePeriod};
	static constexpr float sA{cFilterAlpha};
};

#endif
