#ifndef TACTIONHOLDER_H
#define TACTIONHOLDER_H
#include "CNulltype.h"

template<class Action, class Base>
class TActionHolder: public Base, public Action
{
public:
	void calculate(const typename Action::InputType& input)
	{
		Action::calculate(input);
		Base::calculate(Action::getOutput());
	}
	void reset()
	{
		Action::reset();
		Base::reset();
	}
	void reloadConfiguration()
	{
		Action::reloadConfiguration();
		Base::reloadConfiguration();
	}
public:
	TActionHolder() = default;
	TActionHolder(const TActionHolder&) = delete;
	TActionHolder& operator=(const TActionHolder&) = delete;
	~TActionHolder() = default;
};

template<class Action>
class TActionHolder<Action, CNulltype> : public CNulltype, public Action
{
public:
	void calculate(const typename Action::InputType& input)
	{
		Action::calculate(input);
	}
	void reset()
	{
		Action::reset();
	}
	void reloadConfiguration()
	{
		Action::reloadConfiguration();
	}
public:
	TActionHolder() = default;
	TActionHolder(const TActionHolder&) = delete;
	TActionHolder& operator=(const TActionHolder&) = delete;
	~TActionHolder() = default;
};

#endif
