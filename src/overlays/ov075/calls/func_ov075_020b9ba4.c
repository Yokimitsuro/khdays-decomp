/* Fires one part of the ov036 enemy (x4: ov036/054/074/091) unless actor flag bit 27 forbids
 * it: rotates the part's muzzle offset (+0x1c) by the actor's heading, adds the actor origin
 * (+0x48c) for the spawn position, aims straight back along the heading, takes the kind from
 * the part's +0x19 byte and the speed from its first word, and marks the request 1/2 when the
 * caller asks for the alternate shot and bit 1 of the part's +0x14 byte for the homing variant. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { u8 b0 : 1, b1 : 1; } PartBits;
typedef struct {
    Vec3 pos;
    short f0c, f0e, f10, f12;
    int f14, f18, f1c, f20, f24, f28;
} Params;

extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov022_02091324(char *self, Params *p);
extern short data_0203d210[];

int func_ov075_020b9ba4(char *self, int unused, char *pPart, int bAlt)
{
    Params p;
    Vec3 v;
    Mtx33 m;
    int idx;
    int s;
    int c;

    if ((*(unsigned long long *)self & 0x8000000ULL) == 0) {
        idx = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000) >> 4;
        c = -data_0203d210[idx * 2 + 1];
        s = -data_0203d210[idx * 2];
        MTX_RotY33_(&m, s, c);
        MTX_MultVec33((Vec3 *)(pPart + 0x1c), &m, &v);
        p.f12 = (short)*(int *)pPart;
        VEC_Add((Vec3 *)(self + 0x8c + 0x400), &v, &p.pos);
        v.x = s;
        v.z = c;
        v.y = 0;
        p.f0c = (short)v.x;
        p.f0e = (short)v.y;
        p.f10 = (short)v.z;
        p.f14 = *(signed char *)(pPart + 0x19);
        p.f18 = 0;
        p.f1c = 0;
        p.f20 = 0;
        p.f28 = 0;
        p.f24 = 0;
        if (bAlt != 0) {
            p.f18 = 1;
            p.f20 |= 2;
        }
        if (((PartBits *)(pPart + 0x14))->b1) {
            p.f20 |= 1;
        }
        func_ov022_02091324(self, &p);
    }
    return 0;
}
