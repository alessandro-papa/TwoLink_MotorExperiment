#ifndef COFFSET_H
#define COFFSET_H
#include "CExperimentData.h"

class COffset
{
public:
	using InputType  = CExperimentData;
	using OutputType = CExperimentData;
public:
	const CExperimentData& calculate(const CExperimentData&);
	const CExperimentData& getOutput() const;
	void reset();
	void reloadConfiguration();
	void setSOffset(const float&);
public:
	COffset();
	COffset& operator=(const COffset&) = delete;
	COffset(const COffset&)            = delete;
	~COffset()                         = default;
private:
	CExperimentData mOutput;
	float      		mSOffset;
};

#endif
