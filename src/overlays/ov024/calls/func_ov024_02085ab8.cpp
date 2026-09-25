/* MobiClip: blit one decoded frame, optionally through the deblocking post-filter.
 *
 * In mode 0 the frame's own luma and chroma planes are handed straight to the
 * blitter. Otherwise a pair of working planes is allocated on first use and the
 * frame is copied into them through the deblocking filter at 02092e60 (see
 * tools/mobiclip_deblock.py), which smooths the 8-pixel block edges by the
 * frame's quantiser: mode 2 filters both edge directions, any other non-zero
 * mode only the vertical ones. The blitter then reads the filtered planes.
 * KH Days always passes mode 0, so the filter never runs in the shipped game.
 *
 * Reports zero once every frame the stream holds has been blitted.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct MobiClipDeblockRequest {
    void *pSrcLuma;
    void *pSrcChroma;
    void *pDstLuma;
    void *pDstChroma;
    u32 nWidth;
    u32 nHeight;
    u32 nQuantiser;
    void *pClipTable;
    int bVerticalOnly;
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
    u32 *anQuantiser;       /* per-slot frame QP ring */
    void *pFilteredLuma;
    void *pFilteredChroma;
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
extern void func_ov024_02092e60_unk(MobiClipDeblockRequest *pRequest);
extern void func_ov024_02086004(MobiClipBlitRequest *pRequest);

int func_ov024_02085ab8(MobiClipDecoder *pDecoder, void *pDest, int nWidth,
                        int nMode)
{
    MobiClipDeblockRequest req;

    if (pDecoder->nBlitted >= pDecoder->nBlitTotal) {
        return 0;
    }

    if (nMode != 0) {
        if (pDecoder->pFilteredLuma == 0) {
            pDecoder->pFilteredLuma = func_ov024_02083cf0(pDecoder->nHeight << 8);
            if (pDecoder->pFilteredLuma == 0) {
                return 0;
            }
        }
        if (pDecoder->pFilteredChroma == 0) {
            pDecoder->pFilteredChroma =
                func_ov024_02083cf0((pDecoder->nHeight >> 1) << 8);
            if (pDecoder->pFilteredChroma == 0) {
                return 0;
            }
        }
        req.pSrcLuma = pDecoder->apLuma[pDecoder->nSlot];
        req.pSrcChroma = pDecoder->apChroma[pDecoder->nSlot];
        req.pDstLuma = pDecoder->pFilteredLuma;
        req.pDstChroma = pDecoder->pFilteredChroma;
        req.nWidth = pDecoder->nWidth;
        req.nHeight = pDecoder->nHeight;
        req.nQuantiser = pDecoder->anQuantiser[pDecoder->nSlot];
        req.pClipTable = func_ov024_0208677c();
        if (nMode == 2) {
            req.bVerticalOnly = 0;
        } else {
            req.bVerticalOnly = 1;
        }
        func_ov024_02092e60_unk(&req);
        pDecoder->blit.pLuma = pDecoder->pFilteredLuma;
        pDecoder->blit.pChroma = pDecoder->pFilteredChroma;
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
