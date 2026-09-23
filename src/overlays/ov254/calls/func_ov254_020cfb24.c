/* Orbit tick: the +0xc velocity is the +0x430 partner's +0x2c vector turned by the +0x30 yaw; once
 * the +4 item's +0xad byte clears the node moves to 020cfbdc. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, Mtx33 *m, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov254_020cfbdc(void);

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov254_020cfb24(int *node)
{
    int *state = (int *)node[1];
    Mtx33 m;
    unsigned int idx = ANG2IDX(state[0xc]);

    MTX_RotY33_(&m, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x430) + 0x2c), &m, (Vec3 *)(state + 3));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020cfbdc);
}
