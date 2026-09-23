/* Aim refresh of the ov259 actor: the +0x14 velocity is the +0x414 partner's +0x2c vector turned
 * by the +0x78 heading. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov259_020cdcac(int *node)
{
    int *state = (int *)node[1];
    Mtx33 m;
    Vec3 v;
    unsigned int idx;

    idx = ANG2IDX(state[0x1e]);
    MTX_RotY33_(&m, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    v = *(Vec3 *)(*(int *)(*state + 0x414) + 0x2c);
    MTX_MultVec33(&v, &m, (Vec3 *)(state + 5));
}
