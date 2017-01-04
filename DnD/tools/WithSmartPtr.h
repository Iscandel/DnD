#pragma once

#include <memory>

template<class Derived>
class WithSmartPtr
{
public:
	typedef std::shared_ptr<Derived> ptr;
};

