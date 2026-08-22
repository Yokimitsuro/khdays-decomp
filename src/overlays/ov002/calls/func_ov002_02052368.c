/*
 * Ov002_InitSurfaceContext - clear a surface context and give it its buffers.
 *
 * Wipes the whole 0x654-byte object, copies the six caller-supplied words into
 * +0x10..+0x24, seeds the id at +0x50 to -1 and stores the mode byte. Each of
 * the two buffers is either taken from the caller or allocated from the default
 * expanding heap, and the matching owned flag records which - the context frees
 * only what it allocated. When a source descriptor is supplied its three words
 * are copied in, the pitch is derived from the second parameter, and both
 * surfaces are queued.
 *
 * ARM. Eleven parameters, seven of them on the caller's stack from sp+0x18.
 *
 * The two buffer blocks are written the same way, each storing its owned flag
 * inside both arms. The ROM emits them asymmetrically - the first with two
 * stores, the second sharing one - but that is mwcc merging the second pair on
 * its own; writing the second as a shared tail costs a register and does not
 * match.
 */

typedef struct { int nA; int nB; int nC; } Ov002SurfaceSource;

extern void MIi_CpuClearFast(unsigned int nValue, void *pDst,
                             unsigned int nSize);
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int nSize, int nAlign);
extern void func_ov002_02052794(int nContext);   /* queue both surfaces */

int func_ov002_02052368(int *pCtx, int nWidth, int nHeight, int nWord2,
                        int nWord3, int nWord4, int nWord5, int nBufferA,
                        int nBufferB, Ov002SurfaceSource *pSource,
                        unsigned char nMode)
{
    MIi_CpuClearFast(0, pCtx, 0x654);
    pCtx[0] = 0;
    pCtx[4] = nWidth;
    pCtx[5] = nHeight;
    pCtx[6] = nWord2;
    pCtx[7] = nWord3;
    pCtx[8] = nWord4;
    pCtx[9] = nWord5;
    pCtx[0x14] = -1;
    *(unsigned char *)(pCtx + 3) = nMode;

    if (nBufferA == 0) {
        pCtx[10] = (int)NNS_FndAllocFromDefaultExpHeapEx(0x600, 2);
        pCtx[0xc] = 1;
    } else {
        pCtx[10] = nBufferA;
        pCtx[0xc] = 0;
    }

    if (nBufferB != 0) {
        pCtx[0xb] = nBufferB;
        pCtx[0xd] = 0;
    } else {
        pCtx[0xb] = (int)NNS_FndAllocFromDefaultExpHeapEx(0x600, 2);
        pCtx[0xd] = 1;
    }

    if (pSource != 0) {
        *(Ov002SurfaceSource *)(pCtx + 0xe) = *pSource;
        pCtx[0x11] = (nHeight + 0x15) * 0x40;
        func_ov002_02052794((int)pCtx);
    } else {
        pCtx[0xf] = 0;
        pCtx[0x10] = 0;
    }
    return 1;
}
