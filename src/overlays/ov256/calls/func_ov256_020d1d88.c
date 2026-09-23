/* Orbit tick of an ov256 claw: the +0x10 velocity is the +0x390 part's +0x2c vector turned by the
 * +0x54 heading, it aims every frame (+0x50 = 020d1b2c) with the +0x34 target on the +0xc anchor, the
 * +0x60 timer runs and the claw moves (020d1400 1, 3). Each time the part's animation ends the orbit
 * count +0x64 grows and the timer restarts: at 9 the part takes motion 5 and the node moves on to
 * 020d1ed0, otherwise it restarts motion 4. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern int func_ov256_020d1b2c(int *node);
extern void func_ov256_020d1400(int *node, int a, int b);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov256_020d1ed0(void);

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov256_020d1d88(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;

    {
        int idx = ANG2IDX(state[0x15]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x390) + 0x2c), &rot, (Vec3 *)(state + 4));
    state[0x14] = func_ov256_020d1b2c(node);
    *(Vec3 *)(state + 0xd) = *(Vec3 *)state[3];
    state[0x18] += *(int *)(node[0] + 0x2c);
    func_ov256_020d1400(node, 1, 3);
    if (*(u8 *)(*(int *)(*(int *)(*state + 0x390) + 0x3c) + 0xad) != 0) {
        return;
    }
    state[0x19]++;
    *((u8 *)state + 0x6c) = 0;
    if (state[0x19] == 9) {
        state[0x18] = 0;
        func_ov107_020c9ee8(*(int *)(*state + 0x390), 5, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d1ed0);
        return;
    }
    state[0x18] = 0;
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 4, 0);
}
