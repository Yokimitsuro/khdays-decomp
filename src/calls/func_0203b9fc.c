typedef struct {
    short field_00;
    short blend[5];      /* last blend code applied, per track */
    void *boundAnm[5];   /* bound NNSG3dAnmObj*, per track */
} AnimState;

typedef struct {
    short numBlends[5];
    char pad_0a[0x10 - 0xa];
    void **blendAnms[5]; /* blendAnms[track][blendCode] -> NNSG3dAnmObj* */
} BlendTable;

extern void func_0202accc(AnimState *anim, unsigned short nTrack, BlendTable *table, short nBlend);
extern int *func_01fff774(int obj, int track, int value);

void func_0203b9fc(void *self, unsigned short idx, short blend, unsigned char value)
{
    if (blend < 0)
        return;

    BlendTable *table = *(BlendTable **)((char *)self + 0x8c);
    if (table == 0)
        return;

    short v = table->numBlends[idx];
    if (v <= 0 || v <= blend)
        return;

    func_0202accc(*(AnimState **)((char *)self + 0x88), idx, table, blend);

    func_01fff774((int)*(AnimState **)((char *)self + 0x88), idx, 0);

    {
        unsigned char *p = (unsigned char *)self + idx;
        p[0xa8] = value;
        p[0xad] = 1;
    }

    ((unsigned char *)self)[0xb2] &= ~1;

    if (idx != 0)
        return;

    void **anms = (*(BlendTable **)((char *)self + 0x8c))->blendAnms[idx];
    if (anms == 0)
        return;

    void *target = anms[(*(AnimState **)((char *)self + 0x88))->blend[idx]];
    *(int *)(*(int *)((char *)target + 8) + 8) |= 1;
    *(int *)(*(int *)((char *)target + 8) + 8) |= 2;
}
