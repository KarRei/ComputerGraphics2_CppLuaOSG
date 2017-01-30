/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#ifndef __SHIPCONTROLLER_H__
#define __SHIPCONTROLLER_H__ 


#include <cassert>

#include <osg/ref_ptr>
#include <osgGA/GUIEventHandler>


class Ship;


/**
 * Manipulator to control the ship.
 */
class ShipController: public osgGA::GUIEventHandler {

public:
    ShipController(Ship *ship);
    virtual ~ShipController(void);

    virtual bool handle(const osgGA::GUIEventAdapter &event, osgGA::GUIActionAdapter &action);

private:
    osg::ref_ptr<Ship> _ship;
};


#endif /* __SHIPCONTROLLER_H__ */


/* vi:set tw=78 sw=4 ts=4 et: */
