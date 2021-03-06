#pragma once
#include "ObjectFactory.h"

#include "game/Action.h"
#include "resources/ResourceImageManager.h"
#include "maze/SideDefManager.h"

template<class BaseType, class ObjectType>//, typename ...Args>
class WallFactory : public ObjectFactory<BaseType>//, ObjectType>//, typename ...Args>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///////////////////////////////////////////////////////////////////////////
	WallFactory()
		:ObjectFactory<BaseType>(ObjectStaticType<ObjectType>::get())
	{
	}

	typename BaseType::ptr create() override
	{
		typename BaseType::ptr type = BaseType::ptr(new Side());
		const SideDef& def = SideDefManager::getInstance()->getDef("Wall");
		type->addResourceImage("main", ResourceImageManager::getInstance()->getResource(def.imageId));
		type->setCurrentDrawnImage("main");
		type->setAction(Action::ptr(new WallAction()));
		type->setType(Side::WALL);
		return type;
		//return std::make_shared<ObjectType>(params);
		//return std::make_shared<ObjectType>(std::forward<Args>(args)...);
	}
};

template<class BaseType, class ObjectType>
class VoidFactory : public ObjectFactory<BaseType>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///////////////////////////////////////////////////////////////////////////
	VoidFactory()
		:ObjectFactory<BaseType>(ObjectStaticType<ObjectType>::get())
	{
	}

	typename BaseType::ptr create() override
	{
		typename BaseType::ptr type = BaseType::ptr(new Side());
		type->setAction(Action::ptr(new Action()));
		type->setType(Side::VOID);
		return type;
		//return std::make_shared<ObjectType>(params);
		//return std::make_shared<ObjectType>(std::forward<Args>(args)...);
	}
};

template<class BaseType, class ObjectType>
class DoorFactory : public ObjectFactory<BaseType>
{
public:
	///////////////////////////////////////////////////////////////////////////
	/// \brief Constructor.
	///////////////////////////////////////////////////////////////////////////
	DoorFactory()
		:ObjectFactory<BaseType>(ObjectStaticType<ObjectType>::get())
	{
	}

	typename BaseType::ptr create() override
	{
		typename BaseType::ptr type = BaseType::ptr(new Side());
		const SideDef& def = SideDefManager::getInstance()->getDef("Door");
		type->addResourceImage("main", ResourceImageManager::getInstance()->getResource(def.imageId));
		type->setCurrentDrawnImage("main");
		//SideDefManager::getInstance()->getResource("door");
		type->setAction(Action::ptr(new DoorAction()));
		type->setType(Side::DOOR);
		return type;
		//return std::make_shared<ObjectType>(params);
		//return std::make_shared<ObjectType>(std::forward<Args>(args)...);
	}
};