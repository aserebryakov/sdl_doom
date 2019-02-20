cmake_minimum_required(VERSION 3.5)

project(sdl_doom)

set(GCC_COMPILE_FLAGS "-m32 -g -Wall -DNORMALUNIX -DLINUX -DSDL")

# LDFLAGS=-L/usr/lib/i386-linux-gnu/
set(GCC__LINK_FLAGS "-L/usr/lib/i386-linux-gnu/ -lSDL -lSDLmain -lm")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COMPILE_FLAGS} ${GCC__LINK_FLAGS}")

# This section should be uncommented if everithing will be moved to x64 arch
# find_package(SDL REQUIRED)
# if (SDL_FOUND)
# 	include_directories(${SDL_INCLUDE_DIR})
# 	link_libraries(${SDL_LIBRARY})
# endif (SDL_FOUND)

add_executable(sdl_doom
	am_map.c
	am_map.h
	d_englsh.h
	d_event.h
	d_french.h
	d_items.c
	d_items.h
	d_main.c
	d_main.h
	d_net.c
	d_net.h
	doomdata.h
	doomdef.c
	doomdef.h
	doomstat.c
	doomstat.h
	doomtype.h
	d_player.h
	dstrings.c
	dstrings.h
	d_textur.h
	d_think.h
	d_ticcmd.h
	f_finale.c
	f_finale.h
	f_wipe.c
	f_wipe.h
	g_game.c
	g_game.h
	hu_lib.c
	hu_lib.h
	hu_stuff.c
	hu_stuff.h
	i_main.c
	i_net.c
	i_net.h
	info.c
	info.h
	i_sdl_video.c
	i_sdl_video.h
	i_sound.c
	i_sound.h
	i_system.c
	i_system.h
	m_argv.c
	m_argv.h
	m_bbox.c
	m_bbox.h
	m_cheat.c
	m_cheat.h
	m_fixed.c
	m_fixed.h
	m_menu.c
	m_menu.h
	m_misc.c
	m_misc.h
	m_random.c
	m_random.h
	m_swap.c
	m_swap.h
	p_ceilng.c
	p_doors.c
	p_enemy.c
	p_floor.c
	p_inter.c
	p_inter.h
	p_lights.c
	p_local.h
	p_map.c
	p_maputl.c
	p_mobj.c
	p_mobj.h
	p_plats.c
	p_pspr.c
	p_pspr.h
	p_saveg.c
	p_saveg.h
	p_setup.c
	p_setup.h
	p_sight.c
	p_spec.c
	p_spec.h
	p_switch.c
	p_telept.c
	p_tick.c
	p_tick.h
	p_user.c
	r_bsp.c
	r_bsp.h
	r_data.c
	r_data.h
	r_defs.h
	r_draw.c
	r_draw.h
	r_local.h
	r_main.c
	r_main.h
	r_plane.c
	r_plane.h
	r_segs.c
	r_segs.h
	r_sky.c
	r_sky.h
	r_state.h
	r_things.c
	r_things.h
	sounds.c
	sounds.h
	s_sound.c
	s_sound.h
	st_lib.c
	st_lib.h
	st_stuff.c
	st_stuff.h
	tables.c
	tables.h
	v_video.c
	v_video.h
	wi_stuff.c
	wi_stuff.h
	w_wad.c
	w_wad.h
	z_zone.c
	z_zone.h
)
