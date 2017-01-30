/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#ifndef __ENTITY__H__
#define __ENTITY__H__ 


#include <osg/ref_ptr>
#include <osg/MatrixTransform>
#include <osg/NodeCallback>



/**
 * Class representing an entity.
 */
class Entity: public osg::NodeCallback {

public:
    virtual ~Entity(void) {}

    osg::Node *getVisual(void)
        { return _visual.get(); }

    virtual void operator()(osg::Node *node, osg::NodeVisitor *visitor);
 
protected:
    Entity(osg::MatrixTransform *visual);

    virtual void onUpdate(double time)
        { /* TODO: Override in sub-classes! */ }

    osg::ref_ptr<osg::MatrixTransform> _visual;
};


#endif /* __ENTITY__H__ */


/* vi:set tw=78 sw=4 ts=4 et: */
