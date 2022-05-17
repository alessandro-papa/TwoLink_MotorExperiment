#ifndef TLINHIERARCHY_H
#define TLINHIERARCHY_H
#include "Global.h"
#include "CNulltype.h"

template<template<class, class>class Holder, class NextAtomicType, class... AtomicTypeList>
class TLinHierarchy : public Holder<NextAtomicType, TLinHierarchy<Holder, AtomicTypeList...>>
{

};

template<template<class, class>class Holder, class LastAtomicType>
class TLinHierarchy<Holder, LastAtomicType> : public Holder<LastAtomicType, CNulltype>
{

};

#endif
