#pragma once

#include "tools\WithSmartPtr.h"

class Action : public WithSmartPtr<Action>
{
public:
	Action();
	~Action();
};

class WallAction : public Action
{

};

class DoorAction : public Action
{

};
