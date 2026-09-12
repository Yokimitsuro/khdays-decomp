typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } MtxFx33;

extern void MTX_RotY33_(MtxFx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const MtxFx33 *m, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern char *data_ov074_020b9b80;
extern short data_0203d210[];

Vec3 func_ov074_020b8b6c(char *self) {
    Vec3 p;
    Vec3 v;
    MtxFx33 m;
    char *base = data_ov074_020b9b80;
    char *blk;
    char *blk2;
    unsigned short a;
    int i;
    blk = base + 0xa4;
    blk2 = blk + 0x2c00;
    p = *(Vec3 *)(self + 0x8c + 0x400);
    a = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    i = a >> 4;
    MTX_RotY33_(&m, data_0203d210[i * 2], data_0203d210[i * 2 + 1]);
    MTX_MultVec33((Vec3 *)(blk2 + 0x124), &m, &v);
    VEC_Add(&v, &p, &p);
    return p;
}
