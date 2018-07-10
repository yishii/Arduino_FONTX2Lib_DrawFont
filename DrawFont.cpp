/*
  Arduino FONTX2 drawing library DrawFont
  https://github.com/yishii/Arduino_FONTX2Lib_DrawFont

  Author : Yasuhiro ISHII
  Date : 6/12/2013

  This software is distributed under the license of Apache2.0
 */
#include <stdbool.h>
#include <VGA.h>
#include <font_common.h>
#include <fontdrv.h>
#include <encoding.h>

static int font_width_ascii = 0;
static int font_height_ascii = 0;
static int font_width_kanji = 0;
static int font_height_kanji = 0;

void drawFontInit(void)
{
    init_fontdrv();
    get_fontGeometry(&font_width_ascii,&font_height_ascii,&font_width_kanji,&font_width_kanji);
}

/*
  put kanji : this function treats the kanji character as fixed 16x16.
*/
static void put_kanji(unsigned char* ptr,int x,int y,int color,int bgcolor,bool fill_bg){
    int lx,ly;
    unsigned short buff;
    
    for (ly = 0;ly < 16;ly++){
	buff = SWITCH_ENDIAN_US((*((unsigned short*)ptr + ly)));
	for (lx = 0;lx < 16;lx++){
	    if ((buff >> 15-lx) & 0x01){
		VGA.drawPixel(lx + x,ly + y,color);
	    } else if(fill_bg){
		VGA.drawPixel(lx + x,ly + y,bgcolor);
	    }
	}
    }
}

/*
  put ascii : this function treats the ascii character as fixed 16x8(heightxwidth).
*/
static void put_ascii(unsigned char* ptr,int x,int y,int color,int bgcolor,bool fill_bg){
    int lx,ly;
    unsigned short buff;
    
    for (ly = 0;ly < 16;ly++){
	buff = *(ptr + ly);
	for (lx = 0;lx < 8;lx++){
	    if ((buff >> 7-lx) & 0x01){
		VGA.drawPixel(lx + x,ly + y,color);
	    } else if(fill_bg){
		VGA.drawPixel(lx + x,ly + y,bgcolor);
	    }
	}
    }
}

void drawFontKanji(unsigned short code,int x,int y,int color,int bgcolor,bool fill_bg)
{
    unsigned char* ptr;
    ptr = GetFontPtr_Kanji(code);
    put_kanji(ptr,x,y,color,bgcolor,fill_bg);
}

void drawFontAscii(unsigned char code,int x,int y,int color,int bgcolor,bool fill_bg)
{
    unsigned char* ptr;
    ptr = GetFontPtr_Ascii(code);
    put_ascii(ptr,x,y,color,bgcolor,fill_bg);
}

/*
  Draw SJIS String
*/
void drawFontString_SJIS(unsigned char* str,int x,int y,int color,int bgcolor,bool fill_bg)
{
    unsigned char* ptr;
    while (*str){
	if(*(str) < 0x80){
	    // 1ƒoƒCƒgŒn”¼Šp•¶Žš
	    ptr = GetFontPtr_Ascii(*str);
	    put_ascii(ptr,x,y,color,bgcolor,fill_bg);
	    x += font_width_ascii;
	    str++;
	} else {
	    // 2ƒoƒCƒgŒn‘SŠp•¶Žš
	    ptr = GetFontPtr_Kanji(*(str) << 8 | *(str+1));
	    put_kanji(ptr,x,y,color,bgcolor,fill_bg);
	    x += font_width_kanji;
	    str+=2;
	}
    }
}

/*
  Draw UTF-8 String
*/
int drawFontString_UTF8(unsigned char* str,int x,int y,int color,int bgcolor,bool fill_bg)
{
    int i;
    int len;
    int lentotal;
    unsigned short jiscode;
    unsigned short sjiscode;
    unsigned short utf16;

    lentotal = 0;
    while(*str != 0x00){
	utf16 = econv_from_utf8_to_utf16(str,&len);
	str += len;
	lentotal += len;
	if((utf16 & 0xff00) == 0x0000){
	    drawFontAscii((unsigned char)(utf16 & 0xff),x,y,color,bgcolor,fill_bg);
	    x += font_width_ascii;
	} else {
	    jiscode = econv_from_utf16_to_jis(utf16);
	    sjiscode = econv_from_jis_to_sjis(jiscode);
	    drawFontKanji(sjiscode,x,y,color,bgcolor,fill_bg);
	    x += font_width_kanji;
	}
    }
    return(lentotal);
}
