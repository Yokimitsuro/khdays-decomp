extern void func_02014dc4(int *ptr, int arg);
extern void func_02014cd0(void *pRenderObj, void *pAnmObj);

/* pAnim: per-track animation binding state, embeds an NNSG3dRenderObj at +0x20. */
typedef struct {
    short field_00;
    short blend[5];      /* last blend code applied, per track */
    void *boundAnm[5];   /* bound NNSG3dAnmObj*, per track */
} AnimState;

/* pTable: per-track array of candidate anim objects, indexed by blend code. */
typedef struct {
    short numBlends[5];
    char pad_0a[0x10 - 0xa];
    void **blendAnms[5]; /* blendAnms[track][blendCode] -> NNSG3dAnmObj* */
} BlendTable;

void func_0202accc(AnimState *anim, unsigned short nTrack, BlendTable *table, short nBlend)
{
    if (table->numBlends[nTrack] == 0)
        return;

    void *cur = anim->boundAnm[nTrack];
    void *target = table->blendAnms[nTrack][nBlend];
    if (cur == target)
        return;

    if (cur != 0)
        func_02014dc4((int *)((char *)anim + 0x20), (int)cur);

    anim->blend[nTrack] = nBlend;
    if (nBlend >= 0) {
        target = table->blendAnms[nTrack][nBlend];
        anim->boundAnm[nTrack] = target;
        func_02014cd0((char *)anim + 0x20, target);

        *(int *)((char *)anim->boundAnm[nTrack] + 4) = 0x1000; /* speed = FX32_ONE */
        *(int *)anim->boundAnm[nTrack] = 0;                    /* frame = 0 */
        return;
    }
    anim->boundAnm[nTrack] = 0;
}
