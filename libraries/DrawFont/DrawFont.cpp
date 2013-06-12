/*
  Arduino FONTX2Lib
  Author : Yasuhiro ISHII
  Date : 6/2/2013
 */

/*
  Graphics Tool Kit (draw FONTX2 fonts)

  Version 0.1

  0.1	: 2005/06/28 : êVãKçÏê¨

*/
#include <VGA.h>
#include <font_common.h>
#include <fontdrv.h>

void drawFontInit(void)
{
    init_fontdrv();
}

static void put_kanji(unsigned char* ptr,int x,int y,int color){
    int lx,ly;
    unsigned short buff;
    
    for (ly = 0;ly < 16;ly++){
	buff = SWITCH_ENDIAN_US((*((unsigned short*)ptr + ly)));
	for (lx = 0;lx < 16;lx++){
	    if ((buff >> 15-lx) & 0x01){
		VGA.drawPixel(lx + x,ly + y,color);
	    }
	}
    }
}

static void put_ascii(unsigned char* ptr,int x,int y,int color){
    int lx,ly;
    unsigned short buff;
    
    for (ly = 0;ly < 16;ly++){
	buff = *(ptr + ly);
	for (lx = 0;lx < 8;lx++){
	    if ((buff >> 7-lx) & 0x01){
		VGA.drawPixel(lx + x,ly + y,color);
	    }
	}
    }
}

void drawFontKanji(unsigned short code,int x,int y,int color)
{
    unsigned char* ptr;
    ptr = GetFontPtr_Kanji(code);
    put_kanji(ptr,x,y,color);
}

void drawFontAscii(unsigned char code,int x,int y,int color)
{
    unsigned char* ptr;
    ptr = GetFontPtr_Ascii(code);
    put_ascii(ptr,x,y,color);
}

void drawFontString(unsigned char* str,int x,int y,int color)
{
    unsigned char* ptr;
    y *= 16;
    while (*str){
	if(*(str) < 0x80){
	    // 1ÉoÉCÉgånîºäpï∂éö
	    ptr = GetFontPtr_Ascii(*str);
	    put_ascii(ptr,x,y,color);
	    x+=8;
	    str++;
	} else {
	    // 2ÉoÉCÉgånëSäpï∂éö
	    ptr = GetFontPtr_Kanji(*(str) << 8 | *(str+1));
	    put_kanji(ptr,x,y,color);
	    x+=16;
	    str+=2;
	}
    }
}
