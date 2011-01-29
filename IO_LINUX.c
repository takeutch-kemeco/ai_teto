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

//#define __LINUX_VGA__

#include <stdio.h>
#include <stdlib.h>

#include <linux/input.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>

#ifdef __LINUX_VGA__
#include <vga.h>
#include <vgagl.h>
#endif //__LINUX_VGA

#include "IO_LINUX.h"

extern void sync_screen(void);

static int 				flg_init_termios = 0;
static struct termios 	save_term;
static struct termios 	temp_term;
static struct timeval	old_tv;
static struct timezone	old_tz;

void* __vsync(void* pParam )
{
	static struct timeval	tv;
	static struct timezone	tz;
	gettimeofday(&tv, &tz);
	
	static struct timespec 	req;
	static struct timespec 	rem;
	req.tv_sec  = 0;
//	req.tv_nsec = 31250000 - (tv.tv_usec - old_tv.tv_usec);		// 1/32(s)
	req.tv_nsec = 15625000 - (tv.tv_usec - old_tv.tv_usec);

	nanosleep(&req,&rem);

	old_tv.tv_usec = tv.tv_usec;
	
	return(0);
}

void vsync(int w)
{
	sync_screen();

	fflush(stdout);

	int i;
	pthread_t pt;

	for(i=0;i<w;i++){
		pthread_create(&pt, NULL, __vsync, NULL );
		pthread_join(pt,NULL);
	}
}

#ifdef __LINUX_VGA__
static int old_set_put_c_s_color  = 0;
static int old_set_put_c_bg_color = 0;
void set_put_c_color( int s_color, int bg_color )
{
/*
	switch(s_color){
	case _COLOR_BLACK:	old_set_put_c_s_color = 0x00; break;
	case _COLOR_RED:	old_set_put_c_s_color = 0xF0; break;
	case _COLOR_GREEN:	old_set_put_c_s_color = 0xCC; break;
	case _COLOR_YELLO:	old_set_put_c_s_color = 0xFC; break;
	case _COLOR_BLUE:	old_set_put_c_s_color = 0xC3; break;
	case _COLOR_PARPLE:	old_set_put_c_s_color = 0xF3; break;
	case _COLOR_LBLUE:	old_set_put_c_s_color = 0xCF; break;
	case _COLOR_WHITE:	old_set_put_c_s_color = 0xFF; break;
	default: 			old_set_put_c_s_color = 0x00; break;
	}

	switch(bg_color){
	case _COLOR_BLACK:	old_set_put_c_bg_color = 0x00; break;
	case _COLOR_RED:	old_set_put_c_bg_color = 0xF0; break;
	case _COLOR_GREEN:	old_set_put_c_bg_color = 0xCC; break;
	case _COLOR_YELLO:	old_set_put_c_bg_color = 0xFC; break;
	case _COLOR_BLUE:	old_set_put_c_bg_color = 0xC3; break;
	case _COLOR_PARPLE:	old_set_put_c_bg_color = 0xF3; break;
	case _COLOR_LBLUE:	old_set_put_c_bg_color = 0xCF; break;
	case _COLOR_WHITE:	old_set_put_c_bg_color = 0xFF; break;
	default: 			old_set_put_c_bg_color = 0x00; break;
	}
*/
	switch(s_color){
	case _COLOR_BLACK:	old_set_put_c_s_color = 0; 	break;
	case _COLOR_RED:	old_set_put_c_s_color = 4;	break;
	case _COLOR_GREEN:	old_set_put_c_s_color = 2;	break;
	case _COLOR_YELLO:	old_set_put_c_s_color = 6;	break;
	case _COLOR_BLUE:	old_set_put_c_s_color = 1;	break;
	case _COLOR_PARPLE:	old_set_put_c_s_color = 13;	break;
	case _COLOR_LBLUE:	old_set_put_c_s_color = 3;	break;
	case _COLOR_ORENGE:	old_set_put_c_s_color = 5;	break;
	case _COLOR_WHITE:	old_set_put_c_s_color = 15;	break;
	default: 			old_set_put_c_s_color = 0;
	}

	switch(bg_color){
	case _COLOR_BLACK:	old_set_put_c_bg_color = 0; 	break;
	case _COLOR_RED:	old_set_put_c_bg_color = 4;		break;
	case _COLOR_GREEN:	old_set_put_c_bg_color = 2;		break;
	case _COLOR_YELLO:	old_set_put_c_bg_color = 6;		break;
	case _COLOR_BLUE:	old_set_put_c_bg_color = 1;		break;
	case _COLOR_PARPLE:	old_set_put_c_bg_color = 13;	break;
	case _COLOR_LBLUE:	old_set_put_c_bg_color = 3;		break;
	case _COLOR_ORENGE:	old_set_put_c_bg_color = 5;		break;
	case _COLOR_WHITE:	old_set_put_c_bg_color = 15;	break;
	default: 			old_set_put_c_bg_color = 0;
	}

	vga_setcolor(old_set_put_c_bg_color);
}
#else
static int old_set_put_c_s_color  = 0;
static int old_set_put_c_bg_color = 0;
void set_put_c_color( int s_color, int bg_color )
{
	switch(s_color){
	case _COLOR_BLACK:	printf("%c[%dm",0x1b, 30 ); break;
	case _COLOR_RED:	printf("%c[%dm",0x1b, 31 ); break;
	case _COLOR_GREEN:	printf("%c[%dm",0x1b, 32 ); break;
	case _COLOR_YELLO:	printf("%c[%dm",0x1b, 33 ); break;
	case _COLOR_BLUE:	printf("%c[%dm",0x1b, 34 ); break;
	case _COLOR_PARPLE:	printf("%c[%dm",0x1b, 35 ); break;
	case _COLOR_LBLUE:	printf("%c[%dm",0x1b, 36 ); break;
	case _COLOR_WHITE:	printf("%c[%dm",0x1b, 37 ); break;
	default: 			printf("%c[%dm",0x1b, 0  ); break;
	}

	switch(bg_color){
	case _COLOR_BLACK:	printf("%c[%dm",0x1b, 40 ); break;
	case _COLOR_RED:	printf("%c[%dm",0x1b, 41 ); break;
	case _COLOR_GREEN:	printf("%c[%dm",0x1b, 42 ); break;
	case _COLOR_YELLO:	printf("%c[%dm",0x1b, 43 ); break;
	case _COLOR_BLUE:	printf("%c[%dm",0x1b, 44 ); break;
	case _COLOR_PARPLE:	printf("%c[%dm",0x1b, 45 ); break;
	case _COLOR_LBLUE:	printf("%c[%dm",0x1b, 46 ); break;
	case _COLOR_WHITE:	printf("%c[%dm",0x1b, 47 ); break;
	default: 			printf("%c[%dm",0x1b, 0  ); break;
	}
	
	old_set_put_c_s_color  = s_color;	old_set_put_c_bg_color = bg_color;
}
#endif // __LINUX_VGA__

#ifdef __LINUX_VGA__
static int old_set_cur_x = 0;
static int old_set_cur_y = 0;
void set_cur( int x, int y )
{
	old_set_cur_x=x;	old_set_cur_y=y;
}
#else
static int old_set_cur_x = 0;
static int old_set_cur_y = 0;
void __set_cur( int x, int y )
{
	if((x>=0&&x<80)&&(y>=0&&y<25)){
		printf("%c[%d;%dH",0x1b, y+1, x+1 );
	}
	else {
		printf("%c[%d;%dH",0x1b, 1, 1 );
	}
	old_set_cur_x=x;	old_set_cur_y=y;
}
void set_cur( int x, int y )
{
	if((x>=0&&x<80)&&(y>=0&&y<25)){
	}
	else {
		x=1;	y=1;
	}
	old_set_cur_x=x;	old_set_cur_y=y;
}

#endif //__LINUX_VGA__

#ifdef __LINUX_VGA__
void clr_scr(void)
{
	vga_clear();
}
#else
void clr_scr(void)
{
	printf("%c[2J",0x1B );
}
#endif //__LINUX_VGA__

#ifdef __LINUX_VGA__
void sync_screen(void){
}

void put_c( unsigned char c )
{
	if((old_set_cur_x>=0&&old_set_cur_x<80)&&(old_set_cur_y>=0&&old_set_cur_y<25)){
		#define PUT_C_W 8
		#define PUT_C_H 16
		int i,j;
		for(j=0;j<PUT_C_H;j++){
			for(i=0;i<PUT_C_W;i++){
				vga_drawpixel(old_set_cur_x*PUT_C_W+i, old_set_cur_y*PUT_C_H+j);
			}
		}
	}
}
#else
#define SCREEN_BUF_W	80
#define SCREEN_BUF_H	25
void __put_c( unsigned char c )
{
	putchar((int)c);
}

static unsigned char SCREEN_BUF_CH[SCREEN_BUF_W*SCREEN_BUF_H];
static int			 SCREEN_BUF_SC[SCREEN_BUF_W*SCREEN_BUF_H];
static int			 SCREEN_BUF_BC[SCREEN_BUF_W*SCREEN_BUF_H];
void put_c( unsigned char c )
{
	if((old_set_cur_x>=0&&old_set_cur_x<80)&&(old_set_cur_y>=0&&old_set_cur_y<25)){
		SCREEN_BUF_CH[old_set_cur_y*SCREEN_BUF_W+old_set_cur_x]=c;
		SCREEN_BUF_SC[old_set_cur_y*SCREEN_BUF_W+old_set_cur_x]=old_set_put_c_s_color;
		SCREEN_BUF_BC[old_set_cur_y*SCREEN_BUF_W+old_set_cur_x]=old_set_put_c_bg_color;
	}
}

static unsigned char PUT_SCREEN_BUF_CH[SCREEN_BUF_W*SCREEN_BUF_H];
static int			 PUT_SCREEN_BUF_SC[SCREEN_BUF_W*SCREEN_BUF_H];
static int			 PUT_SCREEN_BUF_BC[SCREEN_BUF_W*SCREEN_BUF_H];
static int			 PUT_SCREEN_BUF_DF[SCREEN_BUF_W*SCREEN_BUF_H];

void init_screen(void)
{
	int i,j;
	
	unsigned char*	psb_ch = PUT_SCREEN_BUF_CH;
	int* 			psb_sc = PUT_SCREEN_BUF_SC;
	int*			psb_bc = PUT_SCREEN_BUF_BC;
	int*			psb_df = PUT_SCREEN_BUF_DF;

	unsigned char* 	sb_ch = SCREEN_BUF_CH;
	int* 			sb_sc = SCREEN_BUF_SC;
	int* 			sb_bc = SCREEN_BUF_BC;
	
	for(j=0;j<SCREEN_BUF_H;j++){
		for(i=0;i<SCREEN_BUF_W;i++){
			*psb_ch++ = 0;
			*psb_sc++ = 0;
			*psb_bc++ = 0;
			*psb_df++ = 0;

			*sb_ch++ = 0;
			*sb_sc++ = 0;
			*sb_bc++ = 0;
		}
	}	
}

void sync_screen(void)
{
	int i,j;

	unsigned char*	psb_ch = PUT_SCREEN_BUF_CH;
	int* 			psb_sc = PUT_SCREEN_BUF_SC;
	int*			psb_bc = PUT_SCREEN_BUF_BC;
	int*			psb_df = PUT_SCREEN_BUF_DF;

	unsigned char* 	sb_ch = SCREEN_BUF_CH;
	int* 			sb_sc = SCREEN_BUF_SC;
	int* 			sb_bc = SCREEN_BUF_BC;

	for(j=0;j<SCREEN_BUF_H;j++){
		for(i=0;i<SCREEN_BUF_W;i++){
			*psb_df++ = 0;
		}
	}
	psb_df = PUT_SCREEN_BUF_DF;

	for(j=0;j<SCREEN_BUF_H;j++){
		for(i=0;i<SCREEN_BUF_W;i++){
			if( *psb_ch != *sb_ch ){ *psb_ch = *sb_ch;	*psb_df=1; }
			if( *psb_sc != *sb_sc ){ *psb_sc = *sb_sc;	*psb_df=1; }
			if( *psb_bc != *sb_bc ){ *psb_bc = *sb_bc;	*psb_df=1; }
			
			psb_ch++;
			psb_sc++;
			psb_bc++;
			sb_ch++;
			sb_sc++;
			sb_bc++;
			psb_df++;
		}
	}

	psb_ch = PUT_SCREEN_BUF_CH;
	psb_sc = PUT_SCREEN_BUF_SC;
	psb_bc = PUT_SCREEN_BUF_BC;
	psb_df = PUT_SCREEN_BUF_DF;

	for(j=0;j<SCREEN_BUF_H;j++){
		for(i=0;i<SCREEN_BUF_W;i++){
			if( *psb_df != 0 ){
				__set_cur( i, j );
				set_put_c_color( *psb_sc, *psb_bc );
				__put_c( *psb_ch );
			} 

			psb_ch++;
			psb_sc++;
			psb_bc++;
			psb_df++;
		}
	}
}

#endif // __LINUX_VGA__

unsigned char get_c( void )
{
	unsigned char c;
	c = getchar();
	return(c);
}

#ifdef __LINUX_VGA__
void init_sys(void)
{
// 	int vgamode=G1024x768x256;
  	int vgamode=G640x480x256;
	vga_init();
	vga_setmode(vgamode);
	gl_setcontextvga(vgamode);

	if( flg_init_termios == 0 ) {
	  	tcgetattr(fileno(stdin), &save_term);
	  	temp_term = save_term;
	  	temp_term.c_iflag &= ~IGNCR;
	  	temp_term.c_lflag &= ~ICANON;
	  	temp_term.c_lflag &= ~ECHO;
	  	temp_term.c_lflag &= ~ISIG;
	  	temp_term.c_cc[VMIN]=0;
//		temp_term.c_cc[VMIN]=1;
	  	temp_term.c_cc[VTIME]=0;
	  	tcsetattr(fileno(stdin), TCSANOW, &temp_term);
	}
	flg_init_termios += 1;									// ユニークカウンタ（これでシステム全体での起動数を把握しておく）

	srand((unsigned int)time(0));
	
	gettimeofday(&old_tv, &old_tz);
}
#else
void init_sys(void)
{
	init_screen();
	
	if( flg_init_termios == 0 ) {
	  	tcgetattr(fileno(stdin), &save_term);
	  	temp_term = save_term;
	  	temp_term.c_iflag &= ~IGNCR;
	  	temp_term.c_lflag &= ~ICANON;
	  	temp_term.c_lflag &= ~ECHO;
	  	temp_term.c_lflag &= ~ISIG;
	  	temp_term.c_cc[VMIN]=0;
//		temp_term.c_cc[VMIN]=1;
	  	temp_term.c_cc[VTIME]=0;
	  	tcsetattr(fileno(stdin), TCSANOW, &temp_term);
	}
	flg_init_termios += 1;									// ユニークカウンタ（これでシステム全体での起動数を把握しておく）
	
	srand((unsigned int)time(0));
	
	gettimeofday(&old_tv, &old_tz);
}
#endif //__LINUX_VGA__

#ifdef __LINUX_VGA__
void close_sys(void)
{
	flg_init_termios -= 1;									// ユニークカウンタを一つ減らす
	if( flg_init_termios == 0 ) {
		tcsetattr(fileno(stdin), TCSANOW, &save_term );		// すべては、これを複数回起動してしまうのを防止するため。（ユニークカウンタ
	}

	clr_scr();
	set_put_c_color( 0, 0 );
	put_c( '\n');
}
#else
void close_sys(void)
{
	flg_init_termios -= 1;									// ユニークカウンタを一つ減らす
	if( flg_init_termios == 0 ) {
		tcsetattr(fileno(stdin), TCSANOW, &save_term );		// すべては、これを複数回起動してしまうのを防止するため。（ユニークカウンタ
	}

	set_put_c_color( 0, 0 );
	clr_scr();
	__put_c( '\n');
}
#endif //__LINUX_VGA__

int get_rand(void)
{
	return( rand() );
}
