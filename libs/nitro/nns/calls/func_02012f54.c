typedef unsigned short u16;
typedef unsigned long u32;
typedef int BOOL;

typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3
} NNSG2dBGSelect;

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

extern volatile u16 * const data_02041ac0[];

extern void func_020149c4(int *pWidth, int *pHeight, NNSG2dBGSelect bg);
extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern void func_02013484(void *pScreenDst,
                          const NNSG2dScreenData *pScreenData,
                          int srcX, int srcY, int dstX, int dstY,
                          int dstW, int dstH, int width, int height);

static inline BOOL IsMainBG(NNSG2dBGSelect bg)
{
    return bg <= NNS_G2D_BGSELECT_MAIN3;
}

static inline volatile u16 *GetBGnCNT(NNSG2dBGSelect bg)
{
    return data_02041ac0[bg];
}

static inline int GetBGScrOffset(void)
{
    return (int)(0x10000 * ((*(volatile u32 *)0x04000000 & 0x38000000) >> 27));
}

static inline void *GetBGnScrPtr(NNSG2dBGSelect bg)
{
    const int baseBlock = 0x800 * ((*GetBGnCNT(bg) & 0x1f00) >> 8);

    return (void *)((IsMainBG(bg) ? (0x06000000 + GetBGScrOffset())
                                   : 0x06200000) + baseBlock);
}

void func_02012f54(NNSG2dBGSelect bg, const NNSG2dScreenData *pScreenData)
{
    void *pDstBase;
    int plane_cwidth;
    int plane_cheight;
    int load_cwidth;
    int load_cheight;

    pDstBase = GetBGnScrPtr(bg);

    {
        const int scn_cwidth = pScreenData->screenWidth / 8;
        const int scn_cheight = pScreenData->screenHeight / 8;

        func_020149c4(&plane_cwidth, &plane_cheight, bg);
        load_cwidth = (plane_cwidth > scn_cwidth) ? scn_cwidth : plane_cwidth;
        load_cheight = (plane_cheight > scn_cheight) ? scn_cheight : plane_cheight;
    }

    DC_FlushRange((void *)pScreenData->rawData, pScreenData->szByte);
    func_02013484(pDstBase, pScreenData,
                  0, 0, 0, 0,
                  plane_cwidth, plane_cheight,
                  load_cwidth, load_cheight);
}
