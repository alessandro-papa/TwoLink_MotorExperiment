#ifndef CSTATEESTIMATION_H
#define CSTATEESTIMATION_H
#include "CServoSystemData.h"
#include "CExperimentData.h"
#include "ExperimentConfiguration.h"

class CStateEstimation
{
public:
	using InputType  = CServoSystemData;
	using OutputType = CExperimentData;
public:
	const OutputType& calculate(const InputType&);
	const OutputType& getOutput() const;
	void reloadConfiguration();
	void reset();
public:
	CStateEstimation();
	CStateEstimation& operator=(const CStateEstimation&) = delete;
	CStateEstimation(const CStateEstimation&)            = delete;
	~CStateEstimation()                                  = default;
private:
	OutputType mOutput;
	bool       mFirstRun;
	float 	   mTheta0;
	float 	   mPrevious_SRel;
	float 	   mPrevious_Alpha;

	static constexpr float sL_IMU1{0.195F};    	/* Distance from IMU1 to the wheel axis */
	static constexpr float sL_IMU2{0.09F};     	/* Distance from IMU2 to the wheel axis */
	static constexpr float sA{sL_IMU1/sL_IMU2};
	static constexpr float sR_W{0.078F};   		/* radius of the wheels */
	static constexpr float sL{0.43F};   		/* distance between wheels */
	static constexpr float sT{cStateEstimationSamplePeriod};

	static constexpr float sGyro1Limit{4.3F};
};

#endif
