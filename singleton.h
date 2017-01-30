/*
 * CS4085: Skeleton for lab assignment.
 *
 * Copyright (C) 2008 Jacek Rosik <jacek.rosik@ul.ie>
 */


#include <cassert>
#include <cstdlib>


#ifndef __SINGLETON__H__
#define __SINGLETON__H__ 


/**
 * Singleton Design Pattern.
 */
template<typename _Type>
class Singleton {

public:
    virtual ~Singleton(void)
        { assert(_instance == dynamic_cast<_Type *>(this)); _instance = NULL; }

    static _Type *instance(void)
        { return _instance ? _instance : new _Type(); }

protected:
    Singleton(void)
        { assert(_instance == NULL); _instance = dynamic_cast<_Type *>(this); }

private:
    static _Type *_instance;
};


/** The one and only instance.  */
template<typename _Type>
_Type *Singleton<_Type>::_instance = NULL;



#endif /* __SINGLETON__H__ */


/* vi:set tw=78 sw=4 ts=4 et: */
