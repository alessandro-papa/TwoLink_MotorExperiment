#ifndef TSTATEHOLDER_H
#define TSTATEHOLDER_H
#include "AState.h"
#include "CNulltype.h"

template<class State, class Base>
class TStateHolder : public Base
{
public:
	bool tryEntry(CMessage& msg, AState*& statePtr)
	{
		bool consumed = mState.tryEntry(msg, statePtr);
		if(consumed == false)
		{
			return Base::tryEntry(msg, statePtr);
		}
		return true;
	}
public:
	TStateHolder() = default;
	TStateHolder(const TStateHolder&) = delete;
	TStateHolder& operator=(const TStateHolder) = delete;
	virtual ~TStateHolder() = default;
private:
	State mState;
};

template<class State>
class TStateHolder<State, CNulltype> : public CNulltype
{
public:
	bool tryEntry(CMessage& msg, AState*& statePtr)
	{
		return mState.tryEntry(msg, statePtr);
	}
public:
	TStateHolder() = default;
	TStateHolder(const TStateHolder&) = delete;
	TStateHolder& operator=(const TStateHolder&) = delete;
	~TStateHolder() = default;
private:
	State mState;
};

#endif
