#include <stdio.h>
#include <VGA.h>
#include <DrawFont.h>

#define LINE_CONV(x) (x*16)
void setup() {
    VGA.begin(800,600);
    Serial.begin(9600);
    drawFontInit();

    drawFontString_UTF8((unsigned char*)"Arduino VGAライブラリと、自作日本語フォントライブラリのテスト",0,LINE_CONV(2),1,0,false);
    drawFontString_UTF8((unsigned char*)"=============================================================",0,LINE_CONV(3),1,0,false);

    drawFontString_UTF8((unsigned char*)"本日は晴天なり。 ishii.yasuhiro@gmail.com",0,LINE_CONV(6),1,0,false);
    drawFontString_UTF8((unsigned char*)"日本語の漢字データは、FONTX2形式でROM内に保持しています。",0,LINE_CONV(7),1,0,false);
    drawFontString_UTF8((unsigned char*)"Arduino IDEのUTF-8を変換して表示しています。",0,LINE_CONV(8),1,0,false);
}

void loop() {
    char string[64];
    static int i;
  
    sprintf(string,"カウント値 = %04d    ",i++);
    drawFontString_UTF8((unsigned char*)string,0,LINE_CONV(15),1,0,true);
  
}
