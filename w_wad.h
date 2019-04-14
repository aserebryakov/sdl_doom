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
//	WAD I/O functions.
//
//-----------------------------------------------------------------------------


#ifndef __W_WAD__
#define __W_WAD__


#ifdef __GNUG__
#pragma interface
#endif

#include <iostream>
#include <string>
#include <stdint.h>

//
// TYPES
//
typedef struct
{
    // Should be "IWAD" or "PWAD".
    char		identification[4];		
    int			numlumps;
    int			infotableofs;
    
} wadinfo_t;


struct filelump_t
{
    int32_t filepos;
    int32_t size;
    char name[8];
};

inline std::ostream& operator<<(std::ostream& out, const filelump_t lump)
{
    out << "filepos = " << lump.filepos << "\n";
    out << "size = " << lump.size << "\n";
    out << "name = " << std::string{lump.name, 8} << "\n";

    return out;
}

//
// WADFILE I/O related stuff.
//
struct lumpinfo_t
{
    char	name[8];
    int		handle;
    int		position;
    int		size;
};

inline std::ostream& operator<<(std::ostream& out, const lumpinfo_t lump)
{
    out << "name = " << std::string{lump.name, 8} << "\n";
    out << "handle = " << lump.handle << "\n";
    out << "position = " << lump.position << "\n";
    out << "size = " << lump.size << "\n";

    return out;
}


extern	void**		lumpcache;
extern	lumpinfo_t*	lumpinfo;
extern	int		numlumps;

void    W_InitMultipleFiles (char** filenames);
void    W_Reload (void);

int	W_CheckNumForName (char* name);
int	W_GetNumForName (char* name);

int	W_LumpLength (int lump);
void    W_ReadLump (int lump, void *dest);

void*	W_CacheLumpNum (int lump, int tag);
void*	W_CacheLumpName (char* name, int tag);




#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
