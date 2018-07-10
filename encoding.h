/*
  Arduino FONTX2 drawing library DrawFont
  https://github.com/yishii/Arduino_FONTX2Lib_DrawFont

  Author : Yasuhiro ISHII
  Date : 6/2/2013

  This software is distributed under the license of Apache2.0
 */

#ifndef __ENCODING_H__
#define __ENCODING_H__

#if 0
int econv_from_utf8_to_utf16_string(unsigned char* str,unsigned char* converted);
#endif

unsigned short econv_from_jis_to_sjis(unsigned short jis);
unsigned short econv_from_utf16_to_jis(unsigned short utf16);
unsigned short econv_from_utf8_to_utf16(unsigned char* utf8,int* len);

#endif /* __ENCODING_H__ */

