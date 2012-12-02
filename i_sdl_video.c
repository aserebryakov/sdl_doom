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
// $Log:$
//
// DESCRIPTION:
//	DOOM graphics stuff for SDL, Linux.
//
//-----------------------------------------------------------------------------


static const char
rcsid[] = "$Id: i_x.c,v 1.6 1997/02/03 22:45:10 b1 Exp $";

#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "SDL/SDL.h"

#include <stdarg.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <errno.h>
#include <signal.h>

#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

#define POINTER_WARP_COUNTDOWN	1

// SDL pixel color depth
#define SDL_BPP 8

SDL_Surface* screen = NULL;
int		X_width;
int		X_height;

// Blocky mode,
// replace each 320x200 pixel with multiply*multiply pixels.
// According to Dave Taylor, it still is a bonehead thing
// to use ....
static int	multiply=1;


// Graphics initialization with SDL
void I_InitGraphics(void)
{
	static int	firsttime=1;

    if (!firsttime)
	return;
    firsttime = 0;

    signal(SIGINT, (void (*)(int)) I_Quit);

    if (M_CheckParm("-2"))
	multiply = 2;

    if (M_CheckParm("-3"))
	multiply = 3;

    if (M_CheckParm("-4"))
	multiply = 4;

    X_width = SCREENWIDTH * multiply;
    X_height = SCREENHEIGHT * multiply;

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    	I_Error("SDL initializing error");
    }

    screen = SDL_SetVideoMode(X_width, X_height, SDL_BPP, SDL_SWSURFACE);

    if(screen == NULL) {
    	I_Error("SDL setting video mode error");
    }

    if (multiply == 1)
    	screens[0] = (unsigned char *) (screen->pixels);
    else
    	I_Error("Unsupported Mode");

}


void I_ShutdownGraphics(void)
{
  // Freeing SDL screen
  SDL_FreeSurface(screen);
}

void I_UpdateNoBlit (void)
{
	// Do nothing
}

void I_FinishUpdate (void)
{
	SDL_Flip(screen);
}

void I_StartTic (void)
{

}

void I_SetPalette (byte* palette)
{

}

void I_StartFrame (void)
{
    // er?
}

void I_ReadScreen (byte* scr)
{
    memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT);
}
