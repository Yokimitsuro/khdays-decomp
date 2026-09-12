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

void func_0203babc(void *self, unsigned short idx, short blend, unsigned char value)
{
    {
        AnimState *anim = *(AnimState **)((char *)self + 0x88);
        func_0202accc(anim, idx, (BlendTable *)((char *)anim + 0xe0), blend);
    }

    ((unsigned char *)self + idx)[0xa8] = value;
    ((unsigned char *)self + idx)[0xad] = 1;

    {
        AnimState *anim = *(AnimState **)((char *)self + 0x88);
        BlendTable *table = *(BlendTable **)((char *)self + 0x8c);
        void *target = table->blendAnms[idx][anim->blend[idx]];
        int numFrames = *(unsigned short *)(*(int *)((char *)target + 8) + 4);
        func_01fff774((int)anim, idx, (numFrames << 12) - 0x1000);
    }

    ((unsigned char *)self)[0xb2] = (((unsigned char *)self)[0xb2] & ~1) | 1;
}
