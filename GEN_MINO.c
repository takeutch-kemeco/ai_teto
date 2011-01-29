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
#include "POS.h"
#include "GEN_MINO.h"

extern void initDM(GEN_MINO* gen_mimo, POS* cmp );
extern void initGM(GEN_MINO* gen_mino, POS* cmp );

void initGEN_MINO( GEN_MINO* gen_mino, POS* cmp )
{
	int i;
	for(i=0;i<DM_LEN*2;i++){gen_mino->rand_box[i]=i%7;}	//={0,1,2,3,4,5,6,0,1,2,3,4,5,6};
	gen_mino->cur_rand_box_len=DM_LEN*2;
	
	initDM( gen_mino, cmp );
	initGM( gen_mino, cmp );
}

void initDM(GEN_MINO* gen_mimo, POS* cmp )
{
	int i;
	for(i=0;i<DM_LEN;i++){ initMINO( &(gen_mimo->DM[i]),i,cmp ); }
}

void initGM(GEN_MINO* gen_mino, POS* cmp )
{
	int i;
  	for(i=0;i<DM_LEN;i++){ initGHOSTMINO( &(gen_mino->GM[i]),i,cmp ); }
}

void newMINO( MINO* m, MINO* gm, GEN_MINO* gen_mino )
{
	int i; 
	if(gen_mino->cur_rand_box_len<=0){
		for(i=0;i<DM_LEN;i++){gen_mino->rand_box[i+0]=i; gen_mino->rand_box[i+DM_LEN]=i;}
		gen_mino->cur_rand_box_len=DM_LEN;
	}

	int rnd = get_rand() % (gen_mino->cur_rand_box_len);
	cpyMINO(  m, &(gen_mino->DM[(gen_mino->rand_box[rnd])]) );
	cpyMINO( gm, &(gen_mino->GM[(gen_mino->rand_box[rnd])]) );

	for(i=rnd;i<gen_mino->cur_rand_box_len-1;i++){gen_mino->rand_box[i]=gen_mino->rand_box[i+1];}
	gen_mino->cur_rand_box_len--;
}
