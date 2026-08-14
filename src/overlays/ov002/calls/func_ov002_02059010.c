typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    unsigned long long qwStart;
    int nDuration;
    int nPhase;
    int bActive;
    int nField0014;
} Ov002GaugeSlot;

typedef struct {
    u16 wA;
    u16 wB;
} Ov002CountPair;

typedef struct {
    int aHandles[4];                    /* +0x00 */
    u8 pad0010[0x10];
    int nSurface;                       /* +0x20 */
    u8 pad0024[4];
    u8 bDirty;                          /* +0x28 */
    u8 pad0029[7];
    int nSoundState;                    /* +0x30 */
    u8 pad0034[0x14];
    unsigned bTweenB : 1;               /* +0x48 */
    unsigned long long aHold[4];        /* +0x4c */
    Ov002GaugeSlot aSlots[4];           /* +0x6c */
    Ov002CountPair aCounts[4];          /* +0xcc */
    u8 pad00dc[0x18];
    u8 aTweenA[0x1c];                   /* +0xf4 */
    u8 aTweenAState[0x1c];              /* +0x110 */
    u8 aTweenB[0x1c];                   /* +0x12c */
    u8 aTweenBState[0x1c];              /* +0x148 */
    u8 pad0164[0x14];
    int bPromptPending;                 /* +0x178 */
} Ov002SceneCtx;

extern u8 data_0204be04;
extern Ov002SceneCtx *data_ov002_0207f618;
extern int data_ov002_0207ddfc;

extern int func_ov002_02057f60(u8 *pDst, u8 *pSrc, int nMode, int nArg);
extern void func_ov002_02058898(void);
extern void func_ov002_020589b8(void);
extern int func_ov002_0205724c(void);
extern int func_ov002_02058340(int nIndex, Ov002GaugeSlot *pSlot);
extern void GFXi_EnqueueCommand(int nQueue, int nTarget, int nSrc, int nSize);
extern unsigned long long func_020031d4(void);
extern void func_ov002_02057260(int nIndex, int nMode);
extern int func_ov002_0206b7a4(void);
extern void func_02033b24(int nBank, int nSound);
extern void func_02033bb4(int nBank, int nSound, int nFlag);

int func_ov002_02059010(void) {
    int bIdle = 1;
    Ov002SceneCtx *ctx = data_ov002_0207f618;
    int i;
    Ov002GaugeSlot *slot;
    int *pTable;

    if (data_0204be04 != 0) {
        return 0;
    }

    if (func_ov002_02057f60(ctx->aTweenAState, ctx->aTweenA, 0,
                            ctx->aHandles[0]) != 0) {
        func_ov002_02058898();
        bIdle = 0;
    }

    if (ctx->bTweenB == 1 &&
        func_ov002_02057f60(ctx->aTweenBState, ctx->aTweenB, 1,
                            ctx->nSurface) != 0) {
        func_ov002_020589b8();
    }

    if (ctx->bPromptPending != 0 && bIdle != 0) {
        func_ov002_02058898();
    }

    if (func_ov002_0205724c() == 0) {
        slot = ctx->aSlots;
        pTable = &data_ov002_0207ddfc;

        for (i = 0; i < 4; i++) {
            if (func_ov002_02058340(i, slot) != 0) {
                ctx->bDirty = ctx->bDirty | (1 << (i + 3));
            }
            if ((ctx->bDirty & (1 << (i + 3))) != 0) {
                GFXi_EnqueueCommand(7, pTable[0], ctx->aHandles[i], pTable[1]);
            }
            if (ctx->aHold[i] != 0) {
                if (ctx->aHold[i] + 104731 < func_020031d4()) {
                    ctx->aHold[i] = 0;
                    func_ov002_02057260(i, ctx->aCounts[i].wB != 0 ? 0 : 2);
                }
            }
            slot = slot + 1;
            pTable = pTable + 3;
        }

        if ((ctx->bDirty & 2) != 0) {
            GFXi_EnqueueCommand(7, 0x5e0, ctx->nSurface, 0xc0);
        }
        ctx->bDirty = 0;
    }

    if (ctx->nSoundState != 0) {
        if (func_ov002_0206b7a4() != 0) {
            func_02033bb4(0, 8, 5);
            ctx->nSoundState = 0;
        }
    } else {
        if (ctx->aSlots[0].bActive != 0 && func_ov002_0206b7a4() == 0) {
            func_02033b24(0, 8);
            ctx->nSoundState = 1;
        }
    }

    return 0;
}
