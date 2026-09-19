/* Computes a world position for the mission enemy's request slot: picks the local offset of
 * data_ov062_020b7f8c (two Vec3, indexed by slot % 2), rotates it about Y by the model's
 * heading (+0x80, flipped by 0x8000, negated sine/cosine) and adds the actor's +0x48c origin
 * into out. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } MtxFx33;
typedef struct { Vec3 v[2]; } OffsetPair;

extern void MTX_RotY33_(MtxFx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const MtxFx33 *m, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern const OffsetPair data_ov062_020b7f8c;
extern short data_0203d210[];

void func_ov062_020b76f0(char *self, int slot, Vec3 *out)
{
    Vec3 v;
    Vec3 origin;
    MtxFx33 m;
    OffsetPair offsets;
    int i;

    offsets = data_ov062_020b7f8c;
    i = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
    MTX_RotY33_(&m, -data_0203d210[i * 2], -data_0203d210[i * 2 + 1]);
    MTX_MultVec33(&offsets.v[slot % 2], &m, &v);
    origin = *(Vec3 *)(self + 0x8c + 0x400);
    VEC_Add(&v, &origin, out);
}
