#ifndef CEXPERIMENTACTION_H
#define CEXPERIMENTACTION_H
#include "CExperimentActionBase.h"

class CExperimentAction : public CExperimentActionBase
{
public:
	void entryStandby();
	void exitStandby();
public:
	CExperimentAction();
	CExperimentAction(const CExperimentAction&)            = delete;
	CExperimentAction& operator=(const CExperimentAction&) = delete;
	~CExperimentAction()                                   = default;
};

#endif
