/* func_ov245_020d40e8 -- turn planner: clears bit 7 of the actor's +0x60 high byte and, unless
 * the scene's +0xad flag is set, restores pose 1 (020c9264), rotates the +0x3b0 target's +0x14
 * offset by the +0x1c heading (sine table, MTX_RotY33_/MTX_MultVec33) and picks the +0x24 turn:
 * +0.7853 (45 deg) when the rotated x is below -3.5, -0.7853 above 3.5, else a coin toss
 * (RandNextScaled(2)); the turn is added to the heading, +0x2c/+0x30 and the +0x34/+0x35 bytes
 * are cleared and the node moves to 020d4248. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern int func_02023eb4(int scale);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d4248(void);
extern const short data_0203d210[];

void func_ov245_020d40e8(int *node) {
    int *state = (int *)node[1];
    Mtx33 m;
    Vec3 out;
    int idx;

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 1, 0);
    idx = (unsigned short)((0x28BE60DB9391LL * state[7] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    MTX_RotY33_(&m, data_0203d210[(idx >> 4) << 1], data_0203d210[((idx >> 4) << 1) + 1]);
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x3b0) + 0x14), &m, &out);
    if (out.x < -0x3800) {
        state[9] = 0xc91;
    } else if (out.x > 0x3800) {
        state[9] = -0xc91;
    } else {
        state[9] = func_02023eb4(2) != 0 ? 0xc91 : -0xc91;
    }
    state[9] += state[7];
    state[0xc] = 0;
    state[0xb] = 0;
    *((unsigned char *)state + 0x35) = 0;
    *((unsigned char *)state + 0x34) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d4248);
}
