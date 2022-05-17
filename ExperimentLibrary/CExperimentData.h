#ifndef CEXPERIMENTDATA_H
#define CEXPERIMENTDATA_H
#include "Global.h"

class CExperimentData
{
public:
	float mTime;
	float mPhi;
	float mPhiD;
	float mU;
public:
	CExperimentData();
	CExperimentData& operator=(const CExperimentData&) 		= default;
	CExperimentData(const CExperimentData&)                 = default;
	~CExperimentData()                                      = default;
};

#endif
