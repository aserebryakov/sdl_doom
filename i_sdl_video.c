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
    	screens[0] = (byte*) (screen->pixels);
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


//
//	Palette Stuff
//

static SDL_Color colors[256];

void I_SetPalette (byte* palette)
{
    register int	i;
    register int	c;
    static boolean	firstcall = true;

//	TODO: add SDL mode check

	{
	    // initialize the colormap
	    if (firstcall)
	    {
	    	firstcall = false;
	    }

	    // set the X colormap entries
	    for (i=0 ; i<256 ; i++)
	    {
	    	c = gammatable[usegamma][*palette++];
	    	colors[i].r = (c<<8) + c;
	    	c = gammatable[usegamma][*palette++];
	    	colors[i].g = (c<<8) + c;
	    	c = gammatable[usegamma][*palette++];
	    	colors[i].b = (c<<8) + c;
	    }

	    // store the colors to the current colormap
	    SDL_SetColors(screen, colors, 0, 256);

	}
}

void I_StartFrame (void)
{
    // er?
}

void I_ReadScreen (byte* scr)
{
    memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT);
}

int xlatekey(SDL_Event* event)
{

    int rc;

    switch(rc = event->key.keysym.sym)
    {
      case SDLK_LEFT:	rc = KEY_LEFTARROW;	break;
      case SDLK_RIGHT:	rc = KEY_RIGHTARROW;	break;
      case SDLK_DOWN:	rc = KEY_DOWNARROW;	break;
      case SDLK_UP:	rc = KEY_UPARROW;	break;
      case SDLK_ESCAPE:	rc = KEY_ESCAPE;	break;
      case SDLK_RETURN:	rc = KEY_ENTER;		break;
      case SDLK_TAB:	rc = KEY_TAB;		break;
      case SDLK_F1:	rc = KEY_F1;		break;
      case SDLK_F2:	rc = KEY_F2;		break;
      case SDLK_F3:	rc = KEY_F3;		break;
      case SDLK_F4:	rc = KEY_F4;		break;
      case SDLK_F5:	rc = KEY_F5;		break;
      case SDLK_F6:	rc = KEY_F6;		break;
      case SDLK_F7:	rc = KEY_F7;		break;
      case SDLK_F8:	rc = KEY_F8;		break;
      case SDLK_F9:	rc = KEY_F9;		break;
      case SDLK_F10:	rc = KEY_F10;		break;
      case SDLK_F11:	rc = KEY_F11;		break;
      case SDLK_F12:	rc = KEY_F12;		break;

      case SDLK_BACKSPACE:
      case SDLK_DELETE:	rc = KEY_BACKSPACE;	break;

      case SDLK_PAUSE:	rc = KEY_PAUSE;		break;

      case SDLK_KP_EQUALS:
      case SDLK_EQUALS:	rc = KEY_EQUALS;	break;

      case SDLK_KP_MINUS:
      case SDLK_MINUS:	rc = KEY_MINUS;		break;

      case SDLK_RSHIFT:
      case SDLK_LSHIFT:
	rc = KEY_RSHIFT;
	break;

      case SDLK_LCTRL:
      case SDLK_RCTRL:
	rc = KEY_RCTRL;
	break;

      case SDLK_LALT:
      case SDLK_LMETA:
      case SDLK_RALT:
      case SDLK_RMETA:
	rc = KEY_RALT;
	break;

      default:
	if (rc >= SDLK_SPACE && rc <= SDLK_DELETE)
	    rc = rc - SDLK_SPACE + ' ';
	if (rc >= 'A' && rc <= 'Z')
	    rc = rc - 'A' + 'a';
	break;
    }

    return rc;

}


void I_ProcessEvent(SDL_Event* sdl_event)
{
    event_t event;

    // put event-grabbing stuff in here
    switch (sdl_event->type)
    {
      case SDL_KEYDOWN:
	event.type = ev_keydown;
	event.data1 = xlatekey(sdl_event);
	D_PostEvent(&event);
	// fprintf(stderr, "k");
	break;
      case SDL_KEYUP:
	event.type = ev_keyup;
	event.data1 = xlatekey(sdl_event);
	D_PostEvent(&event);
	// fprintf(stderr, "ku");
	break;
/*      case SDL_MOUSEBUTTONDOWN:
	event.type = ev_mouse;
	event.data1 =
	    (X_event.xbutton.state & Button1Mask)
	    | (X_event.xbutton.state & Button2Mask ? 2 : 0)
	    | (X_event.xbutton.state & Button3Mask ? 4 : 0)
	    | (X_event.xbutton.button == Button1)
	    | (X_event.xbutton.button == Button2 ? 2 : 0)
	    | (X_event.xbutton.button == Button3 ? 4 : 0);
	event.data2 = event.data3 = 0;
	D_PostEvent(&event);
	// fprintf(stderr, "b");
	break;
      case SDL_MOUSEBUTTONUP:
	event.type = ev_mouse;
	event.data1 =
	    (X_event.xbutton.state & Button1Mask)
	    | (X_event.xbutton.state & Button2Mask ? 2 : 0)
	    | (X_event.xbutton.state & Button3Mask ? 4 : 0);
	// suggest parentheses around arithmetic in operand of |
	event.data1 =
	    event.data1
	    ^ (X_event.xbutton.button == Button1 ? 1 : 0)
	    ^ (X_event.xbutton.button == Button2 ? 2 : 0)
	    ^ (X_event.xbutton.button == Button3 ? 4 : 0);
	event.data2 = event.data3 = 0;
	D_PostEvent(&event);
	// fprintf(stderr, "bu");
	break;
      case MotionNotify:
	event.type = ev_mouse;
	event.data1 =
	    (X_event.xmotion.state & Button1Mask)
	    | (X_event.xmotion.state & Button2Mask ? 2 : 0)
	    | (X_event.xmotion.state & Button3Mask ? 4 : 0);
	event.data2 = (X_event.xmotion.x - lastmousex) << 2;
	event.data3 = (lastmousey - X_event.xmotion.y) << 2;

	if (event.data2 || event.data3)
	{
	    lastmousex = X_event.xmotion.x;
	    lastmousey = X_event.xmotion.y;
	    if (X_event.xmotion.x != X_width/2 &&
		X_event.xmotion.y != X_height/2)
	    {
		D_PostEvent(&event);
		// fprintf(stderr, "m");
		mousemoved = false;
	    } else
	    {
		mousemoved = true;
	    }
	}
	break;

      case Expose:
      case ConfigureNotify:
	break;
*/
      default:
//	if (doShm && X_event.type == X_shmeventtype) shmFinished = true;
	break;
    }

}


void I_StartTic (void)
{

    if (!screen)
	return;

    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event))
    	I_ProcessEvent(&sdl_event);

    // Warp the pointer back to the middle of the window
    //  or it will wander off - that is, the game will
    //  loose input focus within X11.

/*    if (grabMouse)
    {
	if (!--doPointerWarp)
	{
	    XWarpPointer( X_display,
			  None,
			  X_mainWindow,
			  0, 0,
			  0, 0,
			  X_width/2, X_height/2);

	    doPointerWarp = POINTER_WARP_COUNTDOWN;
	}
    }

    mousemoved = false; */

}
