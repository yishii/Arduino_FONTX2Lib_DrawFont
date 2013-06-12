#ifndef __ENCODING_H__
#define __ENCODING_H__

//int econv_from_utf16_to_jis(unsigned short from,unsigned short* to);
int econv_from_utf8_to_utf16(unsigned char* str,unsigned char* converted);
unsigned short econv_from_jis_to_sjis(unsigned short jis);
unsigned short econv_from_utf16_to_jis(unsigned short utf16);

#endif /* __ENCODING_H__ */

