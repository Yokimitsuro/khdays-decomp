typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef u16 GXScrFmtText;

#define PLANE_WIDTH 32
#define PLANE_HEIGHT 32

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

static inline int CalcTextScreenOffset(int x, int y, int w, int h)
{
    const int x_blk = x / PLANE_WIDTH;
    const int y_blk = y / PLANE_HEIGHT;
    const int x_char = x % PLANE_WIDTH;
    const int y_char = y % PLANE_HEIGHT;
    const int w_blk = w / PLANE_WIDTH;
    const int h_blk = h / PLANE_WIDTH;
    const int blk_w = (x_blk == w_blk) ? (w % PLANE_WIDTH) : PLANE_WIDTH;
    const int blk_h = (y_blk == h_blk) ? (h % PLANE_HEIGHT) : PLANE_HEIGHT;

    return w * PLANE_HEIGHT * y_blk
         + PLANE_WIDTH * blk_h * x_blk
         + blk_w * y_char
         + x_char;
}

void func_020130b0(void *pScreenDst,
                   const NNSG2dScreenData *pScreenData,
                   int srcX, int srcY, int dstX, int dstY,
                   int dstW, int dstH, int width, int height)
{
    {
        const int src_x_end = srcX + width;
        const int src_y_end = srcY + height;
        const int src_next_offset = pScreenData->screenWidth - width;
        const int dst_next_offset = dstW - width;
        const u32 szLine = sizeof(GXScrFmtText) * width;
        const int srcW = pScreenData->screenWidth / 8;
        const int srcH = pScreenData->screenHeight / 8;
        const GXScrFmtText *pSrcBase = (const GXScrFmtText *)pScreenData->rawData;
        GXScrFmtText *pDstBase = (GXScrFmtText *)pScreenDst;
        int sx, sy;
        int dx, dy;

        for (sy = srcY, dy = dstY; sy < src_y_end; sy++, dy++) {
            for (sx = srcX, dx = dstX; sx < src_x_end; sx++, dx++) {
                const GXScrFmtText *pSrc = pSrcBase +
                    CalcTextScreenOffset(sx, sy, srcW, srcH);
                GXScrFmtText *pDst = pDstBase +
                    CalcTextScreenOffset(dx, dy, dstW, dstH);
                *pDst = *pSrc;
            }
        }
    }
}
