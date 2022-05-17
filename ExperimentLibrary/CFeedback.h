#ifndef CFEEDBACK_H
#define CFEEDBACK_H
#include "CExperimentData.h"
#include "EigenDefinition.h"
#include "CServoSystemData.h"

class CFeedback
{
public:
	using InputType  = CExperimentData;
	using OutputType = CExperimentData;
public:
	const CExperimentData& calculate(const CExperimentData& input);
	const CExperimentData& getOutput() const;
	void reloadConfiguration();
	void reset();
	void setSOffset(float offset);
	void useTrialFeedback();
	void usePreTrialFeedback();
public:
	CFeedback();
	CFeedback& operator=(const CFeedback&) = delete;
	CFeedback(const CFeedback&)            = delete;
	~CFeedback()                           = default;
private:
	CMatrix mK;				// dynamic allocation at runtime. TWIPR and Chabo can use this class
	CExperimentData mX;
	float mSOffset;
};

#endif
