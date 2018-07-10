/*
  Arduino FONTX2 Lib

  Coded by Yasuhiro ISHII
*/

/*
  フォントROM定義
*/
#if 0

const volatile unsigned char font_table_kanji[] __attribute__ ((section ("data"))) = {
#include "ILGZ16XF.FNT.INC"
};

const volatile unsigned char font_table_kanji[] = {
#include "ILGZ16XF.FNT.INC"
};

const volatile unsigned char font_table_ascii[] = {
#include "ILGH16XB.FNT.INC"
};

#endif
