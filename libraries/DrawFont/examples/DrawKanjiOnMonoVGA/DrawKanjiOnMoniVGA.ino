#include <VGA.h>
#include <encoding.h>
#include <DrawFont.h>

int econv_from_utf8_to_utf16(unsigned char* str,unsigned char* converted);
unsigned short econv_from_jis_to_sjis(unsigned short jis);
unsigned short econv_from_utf16_to_jis(unsigned short utf16);

void setup() {
    VGA.begin(800,600);
    Serial.begin(9600);
    drawFontInit();
    drawTest("Arduino VGAライブラリと、自作日本語フォントライブラリのテスト",0,32,1);
    drawTest("=============================================================",0,48,1);

    drawTest("本日は晴天なり。 ishii.yasuhiro@gmail.com",0,80,1);
    drawTest("日本語の漢字データは、FONTX2形式でROM内に保持しています。",0,96,1);
    drawTest("Arduino IDEのUTF-8をUTF16→JIS→SJIS変換して表示しています。",0,112,1);
}

int drawTest(const char* str,int x,int y,int color)
{
    int i;
    int len;
    unsigned short jiscode;
    unsigned short sjiscode;
    unsigned char converted[128] = {
	0  };

    len = econv_from_utf8_to_utf16((unsigned char*)str,converted);
    x = 0;
    for(i=0;i<len;i+=2){

	if(converted[i] == 0){
	    drawFontAscii(converted[i+1],x,y,color);
	    x+=8;
	} 
	else {
	    jiscode = econv_from_utf16_to_jis(converted[i]<<8|converted[i+1]);
	    sjiscode = econv_from_jis_to_sjis(jiscode);
	    drawFontKanji(sjiscode,x,y,color);
	    x+=16;
	}    

    }
}

void loop() {
}
