typedef unsigned char u8;
typedef signed short s16;

/* One twelve-byte spawn request as it arrives from the session. */
typedef struct Ov002SpawnRequest {
    u8 nOp;
    char pad001[1];
    s16 nId;
    s16 nSub;
    s16 nX;
    s16 nY;
    s16 nZ;
} Ov002SpawnRequest;

extern char *data_ov002_0207fa00;

extern int func_02030788(void);
extern unsigned int func_ov002_0206fb84(int nOp, Ov002SpawnRequest *pRequest);
extern void *NNSi_FndAllocFromDefaultExpHeap(int nSize);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern void func_02033d0c(int nId, int nSub, int *pPos, int nFlag);

/* Run one spawn request: either spawn it here, or hand it to the session.
 *
 * Any op but 0x18 spawns straight away, the three coordinates scaled up by
 * sixteen into a position triple. Op 0x18 goes to the session instead, under
 * an op that depends on whether this console holds the first seat. If the
 * session answers 0xffff the request is kept, copied into a fresh twelve byte
 * block hung off the context.
 */
void func_ov002_0206e44c(Ov002SpawnRequest *pRequest)
{
    char *pCtx;
    int nOp;
    int aPos[3];

    pCtx = data_ov002_0207fa00;
    if (pRequest->nOp == 0x18) {
        if (func_02030788() == 0) {
            nOp = 0x17;
        } else {
            nOp = 0x18;
        }
        if (func_ov002_0206fb84(nOp, pRequest) != 0xffff) {
            return;
        }
        if (*(void **)(pCtx + 0x8dbc) == 0) {
            return;
        }
        *(void **)(pCtx + 0x8dbc) = NNSi_FndAllocFromDefaultExpHeap(0xc);
        MI_CpuCopy8(pRequest, *(void **)(pCtx + 0x8dbc), 0xc);
    } else {
        aPos[0] = pRequest->nX << 4;
        aPos[1] = pRequest->nY << 4;
        aPos[2] = pRequest->nZ << 4;
        func_02033d0c(pRequest->nId, pRequest->nSub, aPos, 0);
    }
}
