#ifndef ACOMPONENTBASE_H
#define ACOMPONENTBASE_H
#include "IRunnable.h"
#include "CMessageQueue.h"

class AComponentBase : public IRunnable
{
public:
	virtual void init() override = 0;
	virtual void run()  override = 0;
public:
	AComponentBase();
	AComponentBase(const AComponentBase&) = delete;
	AComponentBase& operator=(const AComponentBase&) = delete;
	~AComponentBase() = default;
protected:
	friend class CProxy;
	CMessageQueue mQueue;
};

#endif
