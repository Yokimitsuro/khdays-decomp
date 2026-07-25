#pragma opt_strength_reduction off
/* Ov000_BlitOrClearTileRegion -- clipped tile-region blit or clear.
 *
 * Clamps the request against the 0x20 x 0x18 tile screen (adjusting the source origin
 * and the width/height for any part that falls off the left or top edge), then either
 * copies the rows out of the source blob or clears them, and returns the layer`s new
 * dirty mask.
 *
 * THE PARAMETER IS AN int AND THE CLEAR LOOP REUSES IT AS ITS COUNTER. That is the
 * whole reason this function resisted for so long. The request pointer arrives as a
 * plain integer and is cast to the struct locally; once the clear path no longer needs
 * it, the ORIGINAL SOURCE COUNTS THE ROWS IN THE PARAMETER ITSELF. That is why the
 * clear loop`s counter lives in sl -- sl is the incoming parameter`s register -- while
 * the copy loop`s counter shares r4 with bCopy.
 *
 * Written with a separate local counter instead, the function is one 2-instruction
 * schedule away from matching and NOTHING closes it: 27 compiler builds, 13
 * optimisation levels, every legal pragma, every backend flag, -proc, -ipa, -lang,
 * roughly 2,500 compiled source variants, and an exhaustive sweep of declaration
 * order and block scope all leave the same residue. A counter sitting in a
 * parameter`s register is the tell that the parameter IS the counter.
 *
 * The declaration order below is load-bearing (mwccarm hands out callee-saved
 * registers by declaration rank), and so is `layer` living in the inner block.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov000TileSource {
    u8   pad_00[8];
    u16 *pBlob;
} Ov000TileSource;

typedef struct Ov000BlitRequest {
    u8    pad_00[2];
    short nDstX;
    short nDstY;
    u16   nSrcX;
    u16   nSrcY;
    short nWidth;
    short nHeight;
    u8    pad_0e[2];
    int   nHandle;
    u8    pad_14[4];
    Ov000TileSource *pSource;
} Ov000BlitRequest;

typedef struct Ov000DirtyFlags {
    u8 pad_00[0x10];
    u8 bDirtyMask;
} Ov000DirtyFlags;

extern Ov000DirtyFlags *data_ov000_0205ac28;

extern u16 *func_ov000_02054714(int handle, int *pLayer);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void MIi_CpuClear16(u16 value, void *dst, u32 size);

int func_ov000_0205474c(int nRequest, int bCopy)
{
    u16 *blob;
    int i;
    u32 sx;
    u32 stride;
    u32 sy;
    Ov000BlitRequest *req = (Ov000BlitRequest *)nRequest;
    u16 *dst;
    u32 dx;
    int t;
    int w;
    u32 dy;
    {
        int h;
        int layer;

        dst = func_ov000_02054714(req->nHandle, &layer);
        blob = req->pSource->pBlob;
        w = req->nWidth;
        h = req->nHeight;
        stride = (u32)blob[0] >> 3;
        if (w == -1) {
            w = stride;
        }
        if (h == -1) {
            h = (u32)blob[1] >> 3;
        }
        sx = req->nSrcX;
        sy = req->nSrcY;

        if (req->nDstX < 0) {
            sx = sx - req->nDstX;
            w = w + req->nDstX;
            dx = 0;
        } else {
            dx = (u16)req->nDstX;
        }
        t = dx + w;
        if (t > 0x20) {
            t = t - 0x20;
            w = w - t;
        }
        if (req->nDstY < 0) {
            sy = sy - req->nDstY;
            h = h + req->nDstY;
            dy = 0;
        } else {
            dy = (u16)req->nDstY;
        }
        t = dy + h;
        if (t > 0x18) {
            t = t - 0x18;
            h = h - t;
        }

        if (bCopy != 0) {
            i = 0;
            if (h > 0) {
                do {
                    MIi_CpuCopy16((u16 *)((u8 *)req->pSource->pBlob + 0xc)
                                      + (stride * (sy + i) + sx),
                                  dst + (dx + (dy << 5)), w * 2);
                    i++;
                    dy++;
                } while (i < h);
            }
        } else {
            nRequest = 0;
            if (h > 0) {
                do {
                    MIi_CpuClear16(0, dst + (dx + (dy << 5)), w * 2);
                    nRequest++;
                    dy++;
                } while (nRequest < h);
            }
        }
        {
            int v = data_ov000_0205ac28->bDirtyMask | (1 << layer);
            data_ov000_0205ac28->bDirtyMask = v;
            return v;
        }
    }
}
