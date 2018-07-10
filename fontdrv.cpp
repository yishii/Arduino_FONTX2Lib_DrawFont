/*
  Arduino FONTX2 Lib

  Coded by Yasuhiro ISHII
*/

/**********************************************************************************
  Module       :
  Coded        : Yasuhiro ISHII
  Note         : FONTX2 �h���C�o
  Version      :
  Last updated :
**********************************************************************************/
#include <stdio.h>
#include <font_common.h>
#include <fontdata.h>
#include <fontdrv.h>

const volatile unsigned char font_table_kanji[]
#if 1
 __attribute__ ((section ("text")))
#endif
= {
//#include "ILGZ16XF.FNT.INC"
#include "shnmk16.fnt.INC"
} ;

const volatile unsigned char font_table_ascii[]
#if 1
 __attribute__ ((section ("text")))
#endif
= {
#include "ILGH16XB.FNT.INC"
};

/*
  �����t�H���g�Ɋւ����`
 */
// �t�H���g�T�C�Y(X)
#define	FONT_SIZE_X_KANJI	(((FontX_Kanji*)font_table_kanji)->XSize)
// �t�H���g�T�C�Y(Y)
#define	FONT_SIZE_Y_KANJI	(((FontX_Kanji*)font_table_kanji)->YSize)
// 1�t�H���g�̃T�C�Y(Bytes)
#define FONT_SIZE_KANJI		((FONT_SIZE_X_KANJI >> 3) * FONT_SIZE_Y_KANJI)
// �����R�[�h�^�C�v
#define	FONT_CODE_TYPE_KANJI	(((FontX_Kanji*)font_table_kanji)->CodeType)
// �����Q�ƃe�[�u����
#define	FONT_CODE_TNUM_KANJI	(((FontX_Kanji*)font_table_kanji)->Tnum)
#define FONT_BLOCK_S_KANJI(n)	((((FontX_Kanji*)font_table_kanji)->Block[n]).Start)
#define FONT_BLOCK_E_KANJI(n)	((((FontX_Kanji*)font_table_kanji)->Block[n]).End)

/*
  ASCII�t�H���g�Ɋւ����`
 */
// �t�H���g�T�C�Y(X)
#define	FONT_SIZE_X_ASCII	(((FontX_Ascii*)font_table_ascii)->XSize)
// �t�H���g�T�C�Y(Y)
#define	FONT_SIZE_Y_ASCII	(((FontX_Ascii*)font_table_ascii)->YSize)
// 1�t�H���g�̃T�C�Y(Bytes)
#define FONT_SIZE_ASCII		((FONT_SIZE_X_ASCII >> 3) * FONT_SIZE_Y_ASCII)
// �����R�[�h�^�C�v
#define	FONT_CODE_TYPE_ASCII	(((FontX_Ascii*)font_table_ascii)->CodeType)
// �����f�[�^�X�^�[�g�A�h���X
#define	FONT_DATA_START_ADDR	(((unsigned char*)font_table_ascii) + 17)

static unsigned char* ucpFontDataStart_Kanji;
static unsigned short usFontSearchTable_Kanji[256];

void init_fontdrv(void);
unsigned char* GetFontPtr_Ascii(unsigned char );
unsigned char* GetFontPtr_Kanji(unsigned short );
static int SearchFontAreaNo_Kanji(unsigned short );
int get_fontGeometry(int* font_width_ascii,int* font_height_ascii,int* font_width_kanji,int* font_height_kanji);

/*
  FONTX2 �t�H���g�h���C�o�̏���������

  ���e:
	�t�H���g���f�[�^�ւ̃|�C���^����
	�t�H���g�e�[�u���f�[�^���Q�Ƃ��A�t�H���g�T�[�`�p�̃e�[�u���𐶐�
*/
void init_fontdrv(void){
    int i;
    
    ucpFontDataStart_Kanji = (unsigned char*)(font_table_kanji + FONT_CODE_TNUM_KANJI * 4 + 18);
    
    usFontSearchTable_Kanji[0] = 0;
    
    for (i=1;i<FONT_CODE_TNUM_KANJI;i++){
	usFontSearchTable_Kanji[i] = (FONT_BLOCK_E_KANJI(i-1) - FONT_BLOCK_S_KANJI(i-1) + 1) +
	    usFontSearchTable_Kanji[i-1];
    }
}

int get_fontGeometry(int* font_width_ascii,int* font_height_ascii,int* font_width_kanji,int* font_height_kanji)
{
    *font_width_ascii = FONT_SIZE_X_ASCII;
    *font_height_ascii = FONT_SIZE_Y_ASCII;
    *font_width_kanji = FONT_SIZE_X_KANJI;
    *font_height_kanji = FONT_SIZE_Y_KANJI;

    return(1);
}



/*
  �w�肵��SHIFT-JIS�����R�[�h����AFONTX2�����R�[�h�̃e�[�u��
  ��蕶���f�[�^�̑��݂���G���A�̔ԍ��𓾂�
*/
static int SearchFontAreaNo_Kanji(unsigned short code){
    int i;
    int ret;
    
    for (i=0;i<FONT_CODE_TNUM_KANJI;i++){
	//printf("%04X - %04X : \n",FONT_BLOCK_S_KANJI(i),FONT_BLOCK_E_KANJI(i));
	if((FONT_BLOCK_S_KANJI(i) <= code) && (FONT_BLOCK_E_KANJI(i) >= code)){
	    return(i);
	}
    }
    return (-1);
}

/*
  �w�肵��Ascii�R�[�h����A�Y������t�H���g�f�[�^�̃r�b�g�}�b�v�G���A
  �ւ̃|�C���^�𓾂�
*/
unsigned char* GetFontPtr_Ascii(unsigned char code){
    if (code > 0x7f){
	code = UNKNOWN_CHAR_REPLACE_ASCII;
    }
    return (FONT_DATA_START_ADDR + code * FONT_SIZE_ASCII);
}

/*
  �w�肵��SHIFT-JIS�����R�[�h����A�Y������t�H���g�f�[�^�̃r�b�g�}�b�v
  �G���A�ւ̃|�C���^�𓾂�
*/
unsigned char* GetFontPtr_Kanji(unsigned short code){
    int FontArea;
    unsigned short CodeOffset;
    unsigned long FontStartAddr;
    
    // �w�蕶���R�[�h�̑�����t�H���g�̃G���A���Z�o
    FontArea = SearchFontAreaNo_Kanji(code);
    
    // �����R�[�h�ɊY������t�H���g��������Ȃ��ꍇ
    if (FontArea == -1){
	// �s���Ȃ̂Œu�������p�̃R�[�h�ɑ}���ւ�
	code = UNKNOWN_CHAR_REPLACE_KANJI;
	FontArea = SearchFontAreaNo_Kanji(code);
    }
    
    // �t�H���g�̃u���b�N�擪����̃I�t�Z�b�g�ʎZ�o
    CodeOffset = code - FONT_BLOCK_S_KANJI(FontArea);
    
    // �t�H���g�G���A�擪����̎w��t�H���g�̊J�n�I�t�Z�b�g�ʎZ�o
    FontStartAddr = (usFontSearchTable_Kanji[FontArea] + CodeOffset) * FONT_SIZE_KANJI;

    // �t�H���g�X�^�[�g���A�h���X + �I�t�Z�b�g�ʂ̘a��Ԃ�
    return ((unsigned char*)(ucpFontDataStart_Kanji + FontStartAddr));	
}
