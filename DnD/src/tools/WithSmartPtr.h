#pragma once

#include <memory>

template<class T, typename...MyBases>
class SmartAlias : virtual public MyBases...
{
public:
	typedef std::shared_ptr<T> ptr;
};

class Base : public SmartAlias<Base>
{
};

class Derived : public SmartAlias<Derived, Base>
{
};

class MiniBase : public SmartAlias<MiniBase> {};

class MiniDerived : public SmartAlias<MiniDerived, MiniBase, Derived> {
public:
	MiniDerived() : MiniBase(), Derived()
	{
	}
};

template<class Derived>
class WithSmartPtr
{
public:
	typedef std::shared_ptr<Derived> ptr;
};

