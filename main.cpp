/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */

extern "C" {
#include "lualib.h"
#include "lauxlib.h"

}

#include <cstdlib>

#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include "ship.h"
#include "shipcontroller.h"
#include "world.h"

using namespace std;

list<float> floatList;
lua_State *L;

extern "C" {
  //A function to place all values read from barriers.data in a list
  static int l_cppfunction(lua_State *L){
    //Take out the six parameters that the function was called with from lua and place in cppList
    for (int i = 1; i <= lua_gettop(L); i++){
      floatList.push_back(luaL_checknumber(L,i));
    }
    return 0;
  }
}


#define WINDOW_SIZE                     512

#define WORLD_SIZE                      100.0

/**
 * Initialise the display window camera and projections.
 */
void
initViewer(osgViewer::Viewer &viewer)
{
    /* This will set up a square window (app runs fullscreen by default).  */
    viewer.setUpViewInWindow(0, 0, WINDOW_SIZE, WINDOW_SIZE);

    /* This will create rendering context windows camreras etc... */
    viewer.realize();
    
    /* Set up the camera that it is showing the whole world and does not
     * react to window resizes. The camera is looking at XY plane from above.  */
    osg::ref_ptr<osg::Camera> camera =  viewer.getCamera();
    camera->setProjectionResizePolicy(osg::Camera::FIXED);
    camera->setProjectionMatrixAsOrtho2D(-0.5 * WORLD_SIZE, 0.5 * WORLD_SIZE,
                                         -0.5 * WORLD_SIZE, 0.5 * WORLD_SIZE);
    camera->setViewMatrixAsLookAt(osg::Vec3(0.0, 0.0, 0.0),
                                  osg::Vec3(0.0, 0.0, -1.0),
                                  osg::Vec3(0.0, 1.0, 0.0));
    /* This will disable the manipulator which is useless for us.  */
    camera->setAllowEventFocus(false);
}

/**
 * Create the game world and underlying scene graph.
 */
void
initGameWorld(osgViewer::Viewer &viewer, char* argv[])
{
  World *world = World::instance();

  /* Attach the scene graph to viewer.  */
  viewer.setSceneData(world->getSceneGraph());

  /* Add our space ship to the world.  */
  osg::ref_ptr<Ship> ship = Ship::create();
  world->addEntity(ship.get());

  // very good advice here:
  //http://rubenlaguna.com/wp/2012/11/26/first-steps-lua-cplusplus-integration/

  L = luaL_newstate();
  luaL_openlibs(L);
  
  //Load chunk without executing it
  if(luaL_loadfile(L, "setup.lua")){
    lua_pop(L,1);
  }

  //Execute the lua chunk
  if(lua_pcall(L, 0, LUA_MULTRET, 0)){
    lua_pop(L,1);
  }

  //Register the l_cppfunction to lua and give it the name addBarrier
  lua_pushcfunction(L, l_cppfunction);
  lua_setglobal(L, "addBarrier");

  // Call lua-function read that calls the now registered c++function l_cppfuntion
  lua_getglobal(L, "read");
  lua_pushstring(L, argv[1]);
  lua_pcall(L,1,1,0);
  lua_pop(L,1);

  lua_close(L);

  // Call World::addBarrier-function with the values that is now stored in floatList
  list<float>::iterator it = floatList.begin();
  float barrierValues[6];
  while(it != floatList.end()) {
    //Take the first 6 values(first barrier and place in array, then take the next six and so on...
    for (int s = 0; s < 6; s++) {
      barrierValues[s] = *it;
      it++;
    }
    world->addBarrier(barrierValues[0], barrierValues[1], barrierValues[2], barrierValues[3], barrierValues[4], barrierValues[5]);
  }  

  /* Set up keboard event handler to controll the ship.  */
  viewer.addEventHandler(new ShipController(ship.get()));
}


/**
 * MAIN
 */
int
main(int argc, char *argv[])
{
  /* Create and initialise the viewer.  */
  osgViewer::Viewer viewer;
  initViewer(viewer);

  /* Create the scene.  */
  initGameWorld(viewer, argv);

  /* Enter the event processing loop.  */
  return  viewer.run();
}


/* vi:set tw=78 sw=4 ts=4 et: */
