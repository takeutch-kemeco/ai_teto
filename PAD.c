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

#include "PAD.h"
#include "IO_LINUX.h"

unsigned short PAD1;
unsigned short PAD2;

void syncPAD(void)
{
	int i;
	unsigned char c;
	unsigned short pad_l_nl  = PAD_L_RIGHT | PAD_L_LEFT;

	if( ((PAD1&PAD_L1)!=0) || ((PAD1&PAD_R1)!=0) ) { PAD1 = 0; } else { PAD1 &= pad_l_nl; }
	PAD2 =  0;

	do {
		c=get_c();
		switch(c){
		case 'k': case 'K':	PAD1 |= PAD_R1; 	PAD1|=PAD_L_RIGHT;	break;
		case 'j': case 'J':	PAD1 |= PAD_L1; 	PAD1|=PAD_L_LEFT;	break;
		case 'n': case 'N':	PAD1 |= PAD_L_DOWN;						break;
		case 'i': case 'I':	PAD1 &= ~pad_l_nl; 	PAD1|=PAD_L_RIGHT;	break;
		case 'u': case 'U':	PAD1 &= ~pad_l_nl; 	PAD1|=PAD_L_LEFT;	break;
		case ' ':			PAD1 |= PAD_L_UP;						break;
		case 'f': case 'F':	PAD1 |= PAD_R_UP;	PAD1 &= ~pad_l_nl; 	break;
		case 'd': case 'D':	PAD1 |= PAD_R_LEFT;	PAD1 &= ~pad_l_nl; 	break;
		case 'q': case 'Q':	PAD1 |= PAD_START;	break;
		}
	} while(c!=0xFF);
}
