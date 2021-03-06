/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#include <cassert>
#include <cmath>

#include <osg/Geode>
#include <osg/Quat>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>

#include "ship.h"


Ship::Ship(osg::MatrixTransform *visual):
    Entity(visual), _lastFrame(0.0),
    _power(1.0), _velocity(0.0, 0.0, 0.0)
{
    /* All engines initially disabled.  */
    _engines[0] = false; 
    _engines[1] = false; 
    _engines[2] = false; 
    _engines[3] = false; 
}


Ship *
Ship::create()
{
    osg::ref_ptr<osg::MatrixTransform> visual = new osg::MatrixTransform();

    /* Create visual representation of the ship.  */
    osg::ref_ptr<osg::Cone> shape = new osg::Cone(osg::Vec3(0.0, 0.0, 0.0),  1.0, 3.0);
    shape->setRotation(osg::Quat(0.5 *M_PI, osg::Vec3(1.0, 0.0, 0.0)));

    osg::ref_ptr<osg::Geode>    geode = new osg::Geode;
    geode->addDrawable(new osg::ShapeDrawable(shape.get()));
    visual->addChild(geode.get());

    return new Ship(visual.get());
}


void
Ship::activateEngine(Engine engine, bool activate)
{
    /* Enable/Disable given engine.  */
    assert(engine >= LEFT_ENGINE && engine <= BOTTOM_ENGINE);
    _engines[engine] = activate;
}


void
Ship::translate(const osg::Vec3 translation)
{
    osg::Matrix matrix;
    matrix.makeTranslate(translation);
    _visual->postMult(matrix);
}


void
Ship::rotate(double angle)
{
    osg::Matrix matrix;
    matrix.makeRotate(angle, osg::Vec3(0.0, 0.0, 1.0));
    _visual->postMult(matrix);
}

const osg::Vec3
Ship::getPosition(void) const
{
    osg::Vec3 trans, vdummy;
    osg::Quat qdummy;
    _visual->getMatrix().decompose(trans, qdummy, vdummy, qdummy);

    return trans;
}


double
Ship::getOrientation(void) const
{
    double angle;
    osg::Vec3 vdummy;
    osg::Quat rot, qdummy;
    _visual->getMatrix().decompose(vdummy, rot, vdummy, qdummy);
    rot.getRotate(angle, vdummy);

    return angle;
}



void
Ship::onUpdate(double time)
{
    double delta = time - _lastFrame;
    _lastFrame = time;

    double rot = getOrientation();
    double xdirection = cos(rot+1.57079);
    double ydirection = sin(rot+1.57079);

    /* Get the force vector first.  */
    osg::Vec3 force(0.0, 0.0, 0.0);
    if (_engines[TOP_ENGINE])
        force += osg::Vec3(xdirection, ydirection, 0.0);
    if (_engines[BOTTOM_ENGINE])
        force += osg::Vec3(-xdirection, -ydirection, 0.0);
    force *= _power;

    /* Update ship's position.  */
    // translate(_velocity * delta);

    osg::Vec3 position = getPosition();
    osg::Vec3 trans = _velocity*delta;
    if (position[0] > 50)
      trans[0] = -100;
    else if (position[0] < -50)
      trans[0] = 100;
    else if (position[1] > 50)
      trans[1] = -100;
    else if (position[1] < -50)
      trans[1] = 100;
      
    translate(trans);

    /* Caluclate ship's new velocity.  */
    if (_velocity[0] < 0.8 && _velocity[1] < 0.8) {
      _velocity += force * delta;
    }
    // printf("VELOCITY: %f %f %f\n", _velocity[0], _velocity[1], _velocity[2]);
}


/* vi:set tw=78 sw=4 ts=4 et: */
