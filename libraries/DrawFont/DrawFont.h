/*
  Arduino FONTX2Lib
  Author : Yasuhiro ISHII
  Date : 6/3/2013
 */

#ifndef __DRAWSTRING_H__
#define __DRAWSTRING_H__

void drawFontInit(void);
void drawFontString(unsigned char* str,int x,int y,int color);
void drawFontKanji(unsigned short code,int x,int y,int color);
void drawFontAscii(unsigned char code,int x,int y,int color);

#endif /* __DRAWSTRING_H__ */
