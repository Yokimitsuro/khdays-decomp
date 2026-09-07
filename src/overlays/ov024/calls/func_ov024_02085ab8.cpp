/* MobiClip: blit one decoded frame, optionally through the scaler.
 *
 * With no scaling the frame's own luma and chroma planes are handed straight
 * to the blitter. Otherwise a pair of working planes is allocated on first use
 * and the payload is run through the scaler at 02092e60 into them, with its
 * last argument choosing between the two filter modes; the blitter then reads
 * those instead.
 *
 * Reports zero once every frame the stream holds has been blitted.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct MobiClipScaleRequest {
    void *pSrcLuma;
    void *pSrcChroma;
    void *pDstLuma;
    void *pDstChroma;
    u32 nWidth;
    u32 nHeight;
    void *pPlane;
    void *pTable;
    int bFilter;
};

struct MobiClipBlitRequest {
    void *pLuma;
    void *pChroma;
    void *pDest;
    int nStride;
};

struct MobiClipDecoder {
    u8 pad0000[0x10];
    u32 nWidth;
    u32 nHeight;
    u8 pad0018[0x3c - 0x18];
    MobiClipBlitRequest blit;
    u8 pad004c[0x5c - 0x4c];
    void **apLuma;
    void **apChroma;
    void **apPlanes;
    void *pScaleLuma;
    void *pScaleChroma;
    u8 pad0070[0x9c - 0x70];
    u32 nBlitted;
    u32 nBlitTotal;
    u8 pad00a4[4];
    u32 nSlots;
    u8 pad00ac[0xc4 - 0xac];
    u32 nSlot;
};

extern "C" {

extern void *func_ov024_02083cf0(u32 nSize);
extern void *func_ov024_0208677c(void);
extern void func_ov024_02092e60_unk(MobiClipScaleRequest *pRequest);
extern void func_ov024_02086004(MobiClipBlitRequest *pRequest);

int func_ov024_02085ab8(MobiClipDecoder *pDecoder, void *pDest, int nWidth,
                        int nMode)
{
    MobiClipScaleRequest req;

    if (pDecoder->nBlitted >= pDecoder->nBlitTotal) {
        return 0;
    }

    if (nMode != 0) {
        if (pDecoder->pScaleLuma == 0) {
            pDecoder->pScaleLuma = func_ov024_02083cf0(pDecoder->nHeight << 8);
            if (pDecoder->pScaleLuma == 0) {
                return 0;
            }
        }
        if (pDecoder->pScaleChroma == 0) {
            pDecoder->pScaleChroma =
                func_ov024_02083cf0((pDecoder->nHeight >> 1) << 8);
            if (pDecoder->pScaleChroma == 0) {
                return 0;
            }
        }
        req.pSrcLuma = pDecoder->apLuma[pDecoder->nSlot];
        req.pSrcChroma = pDecoder->apChroma[pDecoder->nSlot];
        req.pDstLuma = pDecoder->pScaleLuma;
        req.pDstChroma = pDecoder->pScaleChroma;
        req.nWidth = pDecoder->nWidth;
        req.nHeight = pDecoder->nHeight;
        req.pPlane = pDecoder->apPlanes[pDecoder->nSlot];
        req.pTable = func_ov024_0208677c();
        if (nMode == 2) {
            req.bFilter = 0;
        } else {
            req.bFilter = 1;
        }
        func_ov024_02092e60_unk(&req);
        pDecoder->blit.pLuma = pDecoder->pScaleLuma;
        pDecoder->blit.pChroma = pDecoder->pScaleChroma;
    } else {
        pDecoder->blit.pLuma = pDecoder->apLuma[pDecoder->nSlot];
        pDecoder->blit.pChroma = pDecoder->apChroma[pDecoder->nSlot];
    }

    pDecoder->blit.pDest = pDest;
    pDecoder->blit.nStride = nWidth << 1;
    func_ov024_02086004(&pDecoder->blit);

    pDecoder->nBlitted = pDecoder->nBlitted + 1;
    pDecoder->nSlot = pDecoder->nSlot + 1;
    if (pDecoder->nSlot == pDecoder->nSlots) {
        pDecoder->nSlot = 0;
    }
    return 1;
}

}
