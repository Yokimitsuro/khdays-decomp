typedef struct { int m[3][3]; } MtxFx33;

extern void MTX_Identity33_(MtxFx33 *mtx);
extern void func_01ff80b8(void);
extern void func_01ff9f00(unsigned int cmd, const void *src, unsigned int words);
extern void func_0201571c(void);

typedef struct {
    char pad_00[0xb8];
    int trans_x;   /* 0xb8 */
    int trans_y;   /* 0xbc */
    int trans_z;   /* 0xc0 */
    int scale_x;   /* 0xc4 */
    int scale_y;   /* 0xc8 */
    int scale_z;   /* 0xcc */
    char pad_d0[0x4];
    unsigned int flags; /* 0xd4 */
} GfxState;

extern GfxState data_02047394;
extern MtxFx33  data_02047428;

void func_02028768(void) {
    MtxFx33 m;
    int cmd_word;

    data_02047394.scale_z = 0x1000;
    data_02047394.scale_y = 0x1000;
    data_02047394.scale_x = 0x1000;
    MTX_Identity33_(&m);
    MTX_Identity33_(&data_02047428);
    data_02047394.trans_z = 0;
    data_02047394.trans_y = 0;
    data_02047394.trans_x = 0;
    data_02047394.flags &= ~0xa4u;
    func_0201571c();
    cmd_word = 0x7fff;
    func_01ff9f00(0x20, &cmd_word, 1);
    func_01ff80b8();
}
