// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// DESCRIPTION:
//	Simple basic typedefs, isolated here to make it easier
//	 separating modules.
//    
//-----------------------------------------------------------------------------


#ifndef __DOOMTYPE__
#define __DOOMTYPE__


#ifndef __BYTEBOOL__
#define __BYTEBOOL__
// Fixed to use builtin bool type with C++.
#ifdef __cplusplus
/**
 * This type is required to fix the issue with sizeof(bool) in GCC
 *
 * Due to the fact that size of boolean type is implementation defined by the
 * standard, it isn't portable and differs from C boolean defined below.
 */
union boolean {
    boolean() :
        val{false}
    {
    }

    boolean(const bool& value) :
        val{value}
    {
    }

    inline operator bool()
    {
        return val;
    }

    inline boolean& operator=(const bool& v)
    {
        val = v;
        return *this;
    }

    inline boolean& operator^=(const bool& v)
    {
        val ^= v;
        return *this;
    }

    bool val;
    int padding;
};

//typedef bool boolean;
#else
typedef enum {false, true} boolean;
#endif
typedef unsigned char byte;
#endif


#include <stdint.h>

// Predefined with some OS.
#ifdef LINUX
#include <values.h>
#else
#define MAXCHAR		((char)0x7f)
#define MAXSHORT	((short)0x7fff)

// Max pos 32-bit int.
#define MAXINT		((int)0x7fffffff)	
#define MAXLONG		((int32_t)0x7fffffff)
#define MINCHAR		((char)0x80)
#define MINSHORT	((short)0x8000)

// Max negative 32-bit integer.
#define MININT		((int)0x80000000)	
#define MINLONG		((int32_t)0x80000000)
#endif




#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
