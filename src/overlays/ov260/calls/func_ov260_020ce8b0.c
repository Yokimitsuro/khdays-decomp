/* Turn tick of the ov260 actor: 020cd794 steers, and the +0x428 rig's offset turned by the +0x64
 * heading is kept in +0x20. Once the +4 rig is idle pose 0xe plays, the rig takes motion 6, effect 5
 * spawns in place, move 0xa starts (020cd148 with the +0x10 argument), the +0x79 flag clears and
 * 020ce9d4 runs next. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern int func_ov260_020cd794(int *node);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void func_ov107_020c9264(int owner, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020ce9d4(void);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov260_020ce8b0(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;

    func_ov260_020cd794(node);
    {
        int idx = ANG2IDX(state[0x19]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x428) + 0x2c), &rot, (Vec3 *)(state + 8));
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 0xe, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x428), 6, 0);
        func_ov107_020c0b90(*state, 5, data_02041dc8, 0);
        func_ov260_020cd148(*state, 0xa, state[4]);
        *((unsigned char *)state + 0x79) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020ce9d4);
        return;
    }
}
