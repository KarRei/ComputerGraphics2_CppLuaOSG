/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#include <osg/Node>
#include <osg/NodeVisitor>
#include <osgUtil/UpdateVisitor>

#include "ship.h"

#include "shipcontroller.h"



ShipController::ShipController(Ship *ship):
    _ship(ship)
{
   assert(ship != NULL);
}

ShipController::~ShipController(void)
{
}


bool
ShipController::handle(const osgGA::GUIEventAdapter &event, osgGA::GUIActionAdapter &action)
{
  osg::Vec3 posit = _ship->getPosition();
    /* Only handle KEYDOWN/UP events.  */
  if (!(event.getEventType() & (osgGA::GUIEventAdapter::KEYDOWN | osgGA::GUIEventAdapter::KEYUP)))
        return false;

    /* Activate the engine one key down event.  */
    bool activate = event.getEventType() == osgGA::GUIEventAdapter::KEYDOWN;

    /* Check which key was pressed and activate the correspoinding engine.  */
    switch (event.getKey()) {
        case osgGA::GUIEventAdapter::KEY_Left:
	  //_ship->activateEngine(Ship::RIGHT_ENGINE, activate);
	  _ship->translate(osg::Vec3(0.0,0.0,0.0)-posit);
	  _ship->rotate(0.1);
	  _ship->translate(posit);
            break;
        case osgGA::GUIEventAdapter::KEY_Up:
            _ship->activateEngine(Ship::BOTTOM_ENGINE, activate);
            break;
        case osgGA::GUIEventAdapter::KEY_Right:
	  //_ship->activateEngine(Ship::LEFT_ENGINE, activate);
	  _ship->translate(osg::Vec3(0.0, 0.0, 0.0)-posit);
	  _ship->rotate(-0.1);
	  _ship->translate(posit);
            break;
        case osgGA::GUIEventAdapter::KEY_Down:
            _ship->activateEngine(Ship::TOP_ENGINE, activate);
            break;
    }

    return false;
}


/* vi:set tw=78 sw=4 ts=4 et: */
