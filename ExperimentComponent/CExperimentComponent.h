#ifndef CEXPERIMENTCOMPONENT_H
#define CEXPERIMENTCOMPONENT_H
#include "AComponentBase.h"
#include "FrameworkConfiguration.h"


class CExperimentComponent : public AComponentBase
{
public:
	void init() override;
	void run() override;
public:
	CExperimentComponent();
	CExperimentComponent& operator=(const CExperimentComponent&) = delete;
	CExperimentComponent(const CExperimentComponent&)            = delete;
	~CExperimentComponent()                                      = default;
private:
	CExperimentFSM mFSM;
};

#endif
