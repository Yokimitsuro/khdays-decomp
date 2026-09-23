/* Drift step of the ov260 actor with a re-check: the +0x20 velocity is its +0x428 part's +0x2c vector
 * turned by the +0x64 heading; once the partner holds no queued move the node ends, queueing move 2
 * unless the target check (020cd540) already picked one. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern int func_ov260_020cd540(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov260_020ce198(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;

    {
        int idx = ANG2IDX(state[0x19]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x428) + 0x2c), &rot, (Vec3 *)(state + 8));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (func_ov260_020cd540(node)) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
