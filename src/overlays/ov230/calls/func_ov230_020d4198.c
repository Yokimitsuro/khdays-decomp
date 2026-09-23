/* Swing tick of the ov230 actor: the +0x4c clock runs up at the frame rate and the +0x490 bone's
 * offset, turned by the +0x40 heading, is kept in +0x10; a hit found by 020d2d90 clears +8. Once the
 * +4 rig is idle pose 0xe plays, move 0xb starts (020d3028), the +0x62 flag clears and brain
 * slot +0x20 runs 020d4298. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern int func_ov230_020d2d90(int *state);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov230_020d3028(int owner, int anim);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov230_020d4298(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov230_020d4198(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;

    state[0x13] += *(int *)(node[0] + 0x2c);
    {
        int idx = ANG2IDX(state[0x10]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x490) + 0x2c), &rot, (Vec3 *)(state + 4));
    if (func_ov230_020d2d90(state) != 0) {
        state[2] = 0;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xe, 0);
    func_ov230_020d3028(*state, 0xb);
    *((unsigned char *)state + 0x62) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov230_020d4298);
}
