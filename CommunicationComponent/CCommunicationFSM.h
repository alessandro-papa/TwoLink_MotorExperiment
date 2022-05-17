// Michael Meindl, 30.05.2019
#ifndef CCOMMUNICATIONFSM_H
#define CCOMMUNICATIONFSM_H
#include "CMessage.h"
#include "CCommunicationAction.h"

class CCommunicationFSM
{
public:
	// name 'StatePtr' denotes a pointer to a class funcion of CCommunicationFSM
	using StatePtr = bool (CCommunicationFSM::*)(CMessage&);
public:
	bool dispatch(CMessage& msg);
	bool onInitial(CMessage& msg);
	bool onConnected(CMessage& msg);
	bool onDisconnected(CMessage& msg);
public:
	CCommunicationFSM();
	CCommunicationFSM& operator=(const CCommunicationFSM&) = delete;
	CCommunicationFSM(const CCommunicationFSM&)            = delete;
	~CCommunicationFSM()                                   = default;
private:
	StatePtr             mState;	// CComm-FSM's current state Ptr
	CCommunicationAction mAction;

	CMessage      mInternalQueue;	// mInternalQueue of 1 CMessage
	Int32         mQueueSize;		// mQueueSize

	// declare possible statePtr of FSM @ compile-time and const (constexpr)
	// and only once within project (static)
	// and initialise with matching member-function
	// declaration + initlialisation needs to be in header at once because of static constexpr
	// compiler needs to know everything
	static constexpr StatePtr sInitial{reinterpret_cast<StatePtr>(&CCommunicationFSM::onInitial)};
	static constexpr StatePtr sConnected{reinterpret_cast<StatePtr>(&CCommunicationFSM::onConnected)};
	static constexpr StatePtr sDisconnected{reinterpret_cast<StatePtr>(&CCommunicationFSM::onDisconnected)};
};

#endif
