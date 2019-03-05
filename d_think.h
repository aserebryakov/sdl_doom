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
//  MapObj data. Map Objects or mobjs are actors, entities,
//  thinker, take-your-pick... anything that moves, acts, or
//  suffers state changes of more or less violent nature.
//
//-----------------------------------------------------------------------------


#ifndef __D_THINK__
#define __D_THINK__


#ifdef __GNUG__
#pragma interface
#endif



//
// Experimental stuff.
// To compile this as "ANSI C with classes"
//  we will need to handle the various
//  action functions cleanly.
//
struct mobj_t;
struct player_t;
struct pspdef_t;
struct thinker_t;

typedef  void (*actionf_v)();
typedef  void (*actionf_p1)(mobj_t*);
typedef  void (*actionf_p2)(player_t*, pspdef_t*);
typedef  void (*actionf_p3)(thinker_t*);

typedef union
{
  actionf_p1	acp1;
  actionf_v	acv;
  actionf_p2	acp2;
  actionf_p3	acp3;
} actionf_t;





// Historically, "think_t" is yet another
//  function pointer to a routine to handle
//  an actor.
typedef actionf_t  think_t;


// Doubly linked list of actors.
struct thinker_t
{
    thinker_t*	prev;
    thinker_t*	next;
    think_t	function;
};



#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
