#include "Side.h"

#include "ObjectFactoryManager.h"
#include "SideFactory.h"

Side::Side()
:GraphicEntity(0)
,myIsRevealed(false)
{
}


Side::~Side()
{
}

struct Void;
struct Wall;
struct Door;

FACTORY_REGISTER_TYPE_WITH_FACTORY(Void, Side, VoidFactory)
FACTORY_REGISTER_TYPE_WITH_FACTORY(Wall, Side, WallFactory)
FACTORY_REGISTER_TYPE_WITH_FACTORY(Door, Side, DoorFactory)
