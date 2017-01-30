/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#include <cassert>
#include <cstdlib>

#include <osg/MatrixTransform>
#include <osg/NodeVisitor>
#include <osgUtil/UpdateVisitor>

#include "entity.h"


Entity::Entity(osg::MatrixTransform *visual):
    _visual(visual)
{
    /* Register itself as a node update callback.  */
    _visual->setUpdateCallback(this);
}

void
Entity::operator()(osg::Node *node, osg::NodeVisitor *visitor)
{
    assert(visitor != NULL);
    assert(visitor->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR);

    /* Call update handler.  */
    const osg::FrameStamp *stamp = visitor->getFrameStamp();
    onUpdate(stamp->getSimulationTime());

    /* Traverse the graph further down the hierarchy.  */
    if (node->getNumChildrenRequiringUpdateTraversal() > 0)
        traverse(node, visitor);
}


/* vi:set tw=78 sw=4 ts=4 et: */
