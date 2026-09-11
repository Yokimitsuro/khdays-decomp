typedef unsigned short u16;

/* Per-track candidate table: numBlends[track] gates whether blendAnms[track]
   is valid, blendAnms[track][blendCode] -> NNSG3dAnmObj*. Matches the
   established BlendTable in src/calls/func_0202accc.c. */
typedef struct {
    u16 numBlends[5];
    char pad_0a[0x10 - 0xa];
    void **blendAnms[5];
} BlendTable;

/* Per-track animation binding state, same object func_0202accc.c's AnimState
   operates on, extended with the fade-transition fields this function reads
   past the embedded NNSG3dRenderObj at +0x20 (only the address is needed
   here, not its layout) up to the default BlendTable at +0xe0. */
typedef struct {
    u16 flags;                /* +0x00, bit 4 = fade transition pending */
    short blend[5];           /* +0x02, blend code currently applied per track */
    void *boundAnm[5];        /* +0x0c, bound NNSG3dAnmObj* per track */
    char pad_20[0xca - 0x20]; /* embedded NNSG3dRenderObj + unexamined fields */
    short pendingBlend[5];    /* +0xca, blend code queued for the fade-in target */
    void *pendingTarget;      /* +0xd4, NNSG3dAnmObj* being faded in */
    int blendWeight;          /* +0xd8, Q12 fade weight applied to the old anim */
    int blendWeightInv;       /* +0xdc */
    BlendTable defaultTable;  /* +0xe0 */
} AnimState;

extern void func_02014dc4(int *ptr, int arg);
extern void func_0202accc(AnimState *anim, u16 nTrack, BlendTable *table, short nBlend);
/* Real definition (libs/nitro/fx/calls/FX_Inv.c) takes one int and ignores
   anything else; this caller evaluates and passes a second, unread argument
   (nFlags scaled to Q12) before the call, which is why the ROM materialises
   that shift right before the bl even though FX_Inv never reads it. */
extern int FX_Inv(int x, int nUnused);
extern void func_02014cd0(void *pRenderObj, void *pAnmObj);

void func_0202ad74(AnimState *anim, u16 nTrack, BlendTable *table, short nBlend, int nFlags)
{
    if (table == 0)
        table = &anim->defaultTable;

    if (anim->flags & 4) {
        void *bound = anim->boundAnm[nTrack];
        if (bound != 0)
            func_02014dc4((int *)((char *)anim + 0x20), (int)bound);
        anim->blend[nTrack] = anim->pendingBlend[nTrack];
        anim->blendWeight = 0x1000;
        anim->pendingBlend[nTrack] = -1;
        anim->boundAnm[nTrack] = anim->pendingTarget;
        anim->pendingTarget = 0;
        anim->flags &= ~4;
    }

    if (nFlags == 0 || anim->blend[nTrack] < 0 || nTrack != 0) {
        func_0202accc(anim, nTrack, table, nBlend);
        return;
    }

    {
        void *target = table->blendAnms[nTrack][nBlend];
        u16 thresh = *(u16 *)((char *)*(void **)((char *)target + 8) + 4);

        if (nFlags > (int)(thresh << 12) >> 12) {
            func_0202accc(anim, nTrack, table, nBlend);
            return;
        }

        if (anim->boundAnm[nTrack] != target) {
            anim->pendingBlend[nTrack] = nBlend;
            anim->blendWeightInv = FX_Inv(0x1000, nFlags << 12);
            anim->blendWeight = 0x1000 - anim->blendWeightInv;

            anim->pendingTarget = table->blendAnms[nTrack][nBlend];
            *(int *)anim->pendingTarget = 0;
            func_02014cd0((char *)anim + 0x20, anim->pendingTarget);

            *(int *)((char *)anim->boundAnm[nTrack] + 4) = anim->blendWeight;
            *(int *)((char *)anim->pendingTarget + 4) = 0x1000 - anim->blendWeight;

            anim->flags |= 4;
        }
    }
}
