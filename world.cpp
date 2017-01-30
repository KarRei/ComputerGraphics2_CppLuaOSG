/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */

#include <osg/Group>

#include <osg/Geometry>		// new
#include <osg/Geode>		// new
#include <osg/ShapeDrawable>	// new

#include "entity.h"

#include "world.h"


World::World(void):
    _root(new osg::Group())
{
}


World::~World(void)
{
}

/**
 * Add entity to the world.
 *
 * The world teakes the ownership of the entity and is responsible for
 * destroying it.
 */
void
World::addEntity(Entity *entity)
{
    _entities.push_back(entity);

    /* Add the visual representation to the scene graph.  */
    _root->addChild(entity->getVisual());
}

// http://code.google.com/p/osgworks/source/browse/trunk/tests/shapes/shapes.cpp?r=415
// and
// http://osgqsg.googlecode.com/svn-history/r2/trunk/Examples/Picking/PickingMain.cpp

//int World::addBarrier(lua_State *L)
void
World::addBarrier(float hx, float hy, float hz, float ox, float oy, float oz)
{
  /*int n = lua_gettop(L); //number of arguments
  float hx = lua_tonumber(L,1);
  float hy = lua_tonumber(L,2);
  float hz = lua_tonumber(L,3);
  float ox = lua_tonumber(L,4);
  float oy = lua_tonumber(L,5);
  float oz = lua_tonumber(L,6);*/
  
  osg::Box * box = new osg::Box();
  box->setHalfLengths( osg::Vec3(hx, hy, hz) );
  osg::ShapeDrawable * shape = new osg::ShapeDrawable( box );

  osg::Geode * geode = new osg::Geode();
  geode->addDrawable( shape );

  osg::MatrixTransform * transform = new osg::MatrixTransform();
  transform->addChild( geode );
  osg::Matrix m;
  m.makeTranslate( ox, oy, oz ); // offset from centre
  transform->setMatrix( m );

  _root->addChild(transform);

  //return 0;
}

/* vi:set tw=78 sw=4 ts=4 et: */
