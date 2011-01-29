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

#include "IO_LINUX.h"
#include "BLOCK.h"

void initB(BLOCK* B)
{
	B->b[0]		=' ';
	B->b[1]		=' ';
	B->p.x		=0;
	B->p.y		=0;
	B->str_col	=0;
	B->bg_col 	=0;
}

void cpyB(BLOCK* dst, BLOCK* src )
{
	dst->b[0]		= src->b[0];
	dst->b[1]		= src->b[1];
	dst->p.x 		= src->p.x;
	dst->p.y 		= src->p.y;
	dst->str_col 	= src->str_col;
	dst->bg_col 	= src->bg_col;
}

void posB(BLOCK* b, int x, int y)
{
	b->p.x=x;
	b->p.y=y;
}

void colB(BLOCK* b, int col)
{
	switch(col){
	case 0:	b->str_col = b->bg_col = _COLOR_BLACK;	break;
//	case 0:	b->str_col = b->bg_col = 0;				break;
	case 1:	b->str_col = b->bg_col = _COLOR_LBLUE;	break;
	case 2:	b->str_col = b->bg_col = _COLOR_ORENGE;	break;
	case 3:	b->str_col = b->bg_col = _COLOR_PARPLE;	break;
	case 4:	b->str_col = b->bg_col = _COLOR_RED;	break;
	case 5:	b->str_col = b->bg_col = _COLOR_GREEN;	break;
	case 6:	b->str_col = b->bg_col = _COLOR_YELLO;	break;
	case 7:	b->str_col = b->bg_col = _COLOR_BLUE;	break;
	case 8:	b->str_col = b->bg_col = _COLOR_WHITE;	break;
	}
}

void colGB(BLOCK* b)
{
	b->b[0] = '[';
	b->b[1] = ']';
	b->str_col = _COLOR_WHITE; b->bg_col = _COLOR_BLACK;
}

void prtB(BLOCK* b, int x, int y)
{
	set_put_c_color(b->str_col,b->bg_col);

	set_cur(2*(b->p.x+x)+0,b->p.y+y+0);		put_c(b->b[0]);
	set_cur(2*(b->p.x+x)+1,b->p.y+y+0);		put_c(b->b[1]);

	set_put_c_color(0,0);	
}

void clrB(BLOCK* b, int x, int y)
{
	set_put_c_color(_COLOR_BLACK,_COLOR_BLACK);

	set_cur(2*(b->p.x+x)+0,b->p.y+y+0);		put_c(b->b[0]);
	set_cur(2*(b->p.x+x)+1,b->p.y+y+0);		put_c(b->b[1]);

	set_put_c_color(0,0);	
}
