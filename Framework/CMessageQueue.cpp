#include "CMessageQueue.h"

CMessageQueue::CMessageQueue() : mQueue{EEvent::DefaultIgnore},
								 mReadSem{false, 0},
								 mWriteSem{false, cMessageQueueSize},
								 mHeadIndex{0U},
								 mTailIndex{0U}
{

}
bool CMessageQueue::push_back(const CMessage& msg, bool waitForever)
{
	if(mWriteSem.take(waitForever) == true)
	{
		mQueue[mTailIndex] = msg;
		mTailIndex == (cMessageQueueSize - 1U) ? mTailIndex = 0U : ++mTailIndex;
		mReadSem.give();
		return true;
	}
	else
	{
		return false;
	}
}
bool CMessageQueue::pop_front(CMessage& msg, bool waitForever)
{
	if(mReadSem.take(waitForever) == true)
	{
		msg = mQueue[mHeadIndex];
		mHeadIndex == (cMessageQueueSize - 1U) ? mHeadIndex = 0U : ++mHeadIndex;
		mWriteSem.give();
		return true;
	}
	else
	{
		return false;
	}
}
