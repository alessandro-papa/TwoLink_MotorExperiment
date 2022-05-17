#ifndef CMESSAGEQUEUE_H
#define CMESSAGEQUEUE_H
#include "CMessage.h"
#include "CCountingSemaphore.h"

constexpr auto cMessageQueueSize{10U};

class CMessageQueue
{
public:
	bool push_back(const CMessage&, bool waitForever);
	bool pop_front(CMessage&, bool waitForever);
public:
	CMessageQueue();
	CMessageQueue(const CMessageQueue&) = delete;
	CMessageQueue& operator=(const CMessageQueue&) = delete;
	~CMessageQueue() = default;
private:
	CMessage                mQueue[cMessageQueueSize];
	CCountingSemaphore      mReadSem;
	CCountingSemaphore      mWriteSem;
	UInt32                  mHeadIndex;
	UInt32                  mTailIndex;
};

#endif
