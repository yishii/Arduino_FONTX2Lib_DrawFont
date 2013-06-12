/*
  Arduino FONTX2Lib
  Author : Yasuhiro ISHII
  Date : 6/3/2013
 */

#ifndef __DRAWSTRING_H__
#define __DRAWSTRING_H__

#include <stdbool.h>

void drawFontInit(void);

void drawFontString_SJIS(unsigned char* str,int x,int y,int color,int bgcolor,bool bg_color);
int drawFontString_UTF8(unsigned char* str,int x,int y,int color,int bgcolor,bool bg_color);

#endif /* __DRAWSTRING_H__ */
