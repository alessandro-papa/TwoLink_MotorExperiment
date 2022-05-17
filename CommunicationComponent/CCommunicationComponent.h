#ifndef CCOMMUNICATIONCOMPONENT_H
#define CCOMMUNICATIONCOMPONENT_H
#include "AComponentBase.h"
#include "FrameworkConfiguration.h"
#include "CCommunicationFSM.h"

class CCommunicationComponent : public AComponentBase
{
public:
	void init() override;
	void run() override;
public:
	CCommunicationComponent();
	CCommunicationComponent& operator=(const CCommunicationComponent&) = delete;
	CCommunicationComponent(const CCommunicationComponent&)            = delete;
	~CCommunicationComponent()                                         = default;
private:
	CCommunicationFSM  mFSM;
};

#endif
