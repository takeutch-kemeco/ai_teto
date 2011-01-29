/*
 * 3-clause BSD license
 * Copyright (c) 2011, Kemeco
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *      * Neither the name of the Kemeco nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Kemeco ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Kemeco BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __IO_LINUX_H__
#define __IO_LINUX_H__

#define _COLOR_BLACK 	1
#define _COLOR_RED 		2
#define _COLOR_GREEN	3
#define _COLOR_YELLO	4
#define _COLOR_BLUE		5
#define _COLOR_PARPLE	6
#define _COLOR_LBLUE	7
#define _COLOR_WHITE	8

#ifdef __LINUX_VGA__
#define _COLOR_ORENGE	9
#else
#define _COLOR_ORENGE	_COLOR_WHITE
#endif //__LINUX_VGA_

extern void vsync(int w);

extern void set_cur( int x, int y );

extern void set_put_c_color( int s_color, int bg_color );
extern void put_c( unsigned char c );
extern unsigned char get_c( void );
extern void clr_scr(void);

extern int get_rand(void);

extern void init_sys(void);
extern void close_sys(void);

#endif //__IO_LINUX_H__
