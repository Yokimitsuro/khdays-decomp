typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 8

void MIi_CpuClearFast(u32 data, void * destp, u32 size);
static inline void MI_CpuFillFast (void * dest, u32 data, u32 size)
{
    MIi_CpuClearFast(data, dest, size);
}
typedef enum {
    PXI_FIFO_TAG_EX = 0,
    PXI_FIFO_TAG_USER_0,
    PXI_FIFO_TAG_USER_1,
    PXI_FIFO_TAG_SYSTEM,
    PXI_FIFO_TAG_NVRAM,
    PXI_FIFO_TAG_RTC,
    PXI_FIFO_TAG_TOUCHPANEL,
    PXI_FIFO_TAG_SOUND,
    PXI_FIFO_TAG_PM,
    PXI_FIFO_TAG_MIC,
    PXI_FIFO_TAG_WM,
    PXI_FIFO_TAG_FS,
    PXI_FIFO_TAG_OS,
    PXI_FIFO_TAG_CTRDG,
    PXI_FIFO_TAG_CARD,
    PXI_FIFO_TAG_WVR,
    PXI_FIFO_TAG_CTRDG_Ex,
    PXI_FIFO_TAG_CTRDG_PHI,
    PXI_MAX_FIFO_TAG = 32
} PXIFifoTag;
typedef void (*PXIFifoCallback) (PXIFifoTag tag, u32 data, BOOL err);
typedef struct NNSG2dCharWidths {
    s8 left;
    u8 glyphWidth;
    s8 charWidth;
} NNSG2dCharWidths;
typedef struct NNSG2dFontGlyph {
    u8 cellWidth;
    u8 cellHeight;
    u16 cellSize;
    s8 baselinePos;
    u8 maxCharWidth;
    u8 bpp;
    u8 flags;
    u8 glyphTable[];
} NNSG2dFontGlyph;
typedef struct NNSG2dFontWidth {
    u16 indexBegin;
    u16 indexEnd;
    struct NNSG2dFontWidth * pNext;
    NNSG2dCharWidths widthTable[];
} NNSG2dFontWidth;
typedef struct NNSG2dFontCodeMap {
    u16 ccodeBegin;
    u16 ccodeEnd;
    u16 mappingMethod;
    u16 reserved;
    struct NNSG2dFontCodeMap * pNext;
    u16 mapInfo[];
} NNSG2dFontCodeMap;
typedef struct NNSG2dFontInformation {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
    NNSG2dCharWidths defaultWidth;
    u8 encoding;
    NNSG2dFontGlyph * pGlyph;
    NNSG2dFontWidth * pWidth;
    NNSG2dFontCodeMap * pMap;
} NNSG2dFontInformation;
typedef u16 (*NNSiG2dSplitCharCallback)(const void ** ppChar);
typedef struct NNSG2dFont {
    NNSG2dFontInformation * pRes;
    NNSiG2dSplitCharCallback cbCharSpliter;
} NNSG2dFont;
typedef struct NNSG2dGlyph {
    const NNSG2dCharWidths * pWidths;
    const u8 * image;
} NNSG2dGlyph;
struct NNSG2dCharCanvas;
typedef void (*NNSiG2dDrawGlyphFunc)(const struct NNSG2dCharCanvas * pCC, const NNSG2dFont * pFont, int x, int y, int cl, const NNSG2dGlyph * pGlyph);
typedef void (*NNSiG2dClearFunc)(const struct NNSG2dCharCanvas * pCC, int cl);
typedef void (*NNSiG2dClearAreaFunc)(const struct NNSG2dCharCanvas * pCC, int cl, int x, int y, int w, int h);
typedef struct NNSiG2dCharCanvasVTable {
    NNSiG2dDrawGlyphFunc pDrawGlyph;
    NNSiG2dClearFunc pClear;
    NNSiG2dClearAreaFunc pClearArea;
} NNSiG2dCharCanvasVTable;
typedef struct NNSG2dCharCanvas {
    u8 * charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    const NNSiG2dCharCanvasVTable * vtable;
} NNSG2dCharCanvas;

/* func_02013900 -- NitroSystem g2d_CharCanvas.c: ClearChar. */
void func_02013900 (void * pChar, int x, int y, int w, int h, u32 cl8, int bpp)
{

    if ((w == CHARACTER_WIDTH) && (h == CHARACTER_HEIGHT)) {
        MI_CpuFillFast(pChar, cl8, (u32)(8 * bpp));
    } else {
        if ( bpp == 4 ) {
            u32 mask;
            u32 data;
            u32 * pLine;
            u32 * pLineEnd;

            {
                u32 x4 = (unsigned int)x * 4;
                u32 rw4 = 32 - (w * 4 + x4);

                mask = (u32)(~0) >> x4;
                mask <<= x4 + rw4;
                mask >>= rw4;

                data = cl8 & mask;
                mask = ~mask;
            }

            pLine = (u32 *)pChar + y;
            pLineEnd = pLine + h;
            for ( ; pLine < pLineEnd; pLine++) {
                *pLine = (*pLine & mask) | data;
            }
        } else {
            u32 mask_0, mask_1;
            u32 data_0, data_1;

            {
                u32 x8 = (unsigned int)x * 8;
                u32 rw8 = 64 - (w * 8 + x8);

                mask_0 = (u32)(~0) >> x8;
                if ( rw8 >= 32 ) {
                    const u32 rw32 = rw8 - 32;
                    mask_0 <<= (x8 + rw32);
                    mask_0 >>= rw32;
                } else {
                    mask_0 <<= x8;
                }

                mask_1 = (u32)(~0) << rw8;
                if ( x8 >= 32 ) {
                    const u32 x32 = x8 - 32;
                    mask_1 >>= (x32 + rw8);
                    mask_1 <<= x32;
                } else {
                    mask_1 >>= rw8;
                }

                data_0 = cl8 & mask_0;
                data_1 = cl8 & mask_1;

                mask_0 = ~mask_0;
                mask_1 = ~mask_1;
            }

            {
                u32 * pLine = (u32 *)((u64 *)pChar + y);
                u32 * const pLineEnd = (u32 *)((u64 *)pLine + h);

                while ( pLine < pLineEnd ) {
                    *pLine = (*pLine & mask_0) | data_0;
                    pLine++;
                    *pLine = (*pLine & mask_1) | data_1;
                    pLine++;
                }
            }
        }
    }
}
