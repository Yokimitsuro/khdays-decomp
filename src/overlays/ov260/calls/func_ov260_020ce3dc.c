/* Glide combo tick of the ov260 actor (stage +0x78): the +0x70 timer accumulates the frame rate and
 * the stage's effect starts once (+0x7b bit 0: 6 at 0x330, 7 at 0x1100, 8 at 0x2288); the second
 * +0x17a flag starts effect 5 once (bit 1); stage 0 cues at 0x440 and 0x770 (020cd04c 2 / 3). The
 * +0x20 velocity is its +0x428 part's +0x2c vector turned by the +0x64 heading and the body sweeps for
 * hits (020cd2a0, the stage as kind; from stage 2 along a segment from its +0x74 position along the
 * velocity, +0x80 wide). Once the partner holds no queued move, stage 2 ends the glide (pose 0x18,
 * motion 0xe, on to 020ce70c); earlier stages re-aim (020cd794), turn to the target, advance and play
 * pose 0x13 + 2 x stage, motion 9 + 2 x stage and effect 0x17 (stage 1) or 0x1a. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct Flag17a { u8 b0 : 1; u8 b1 : 1; };

extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_ov260_020cd04c(int actor, int flag);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_ov260_020cd2a0(int *state, int kind, void *sphere, void *cyl, void *seg);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern int func_ov260_020cd794(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020ce70c(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define STAGE(s) (*((signed char *)(s) + 0x78))

void func_ov260_020ce3dc(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;
    Capsule seg;

    state[0x1c] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0x7b) & 1) == 0) {
        if (STAGE(state) == 0 && state[0x1c] >= 0x330) {
            *((u8 *)state + 0x7b) |= 1;
            func_ov260_020cd148(*state, 6, state[4]);
        } else if (STAGE(state) == 1 && state[0x1c] >= 0x1100) {
            *((u8 *)state + 0x7b) |= 1;
            func_ov260_020cd148(*state, 7, state[4]);
        } else if (STAGE(state) == 2 && state[0x1c] >= 0x2288) {
            *((u8 *)state + 0x7b) |= 1;
            func_ov260_020cd148(*state, 8, state[4]);
        }
    }
    if ((*((u8 *)state + 0x7b) & 2) == 0 && ((struct Flag17a *)(*state + 0x17a))->b1) {
        *((u8 *)state + 0x7b) |= 2;
        func_ov260_020cd148(*state, 5, state[4]);
    }
    if (STAGE(state) == 0) {
        if ((*((u8 *)state + 0x7b) & 4) == 0 && state[0x1c] >= 0x440) {
            *((u8 *)state + 0x7b) |= 4;
            func_ov260_020cd04c(*state, 2);
        }
        if ((*((u8 *)state + 0x7b) & 8) == 0 && state[0x1c] >= 0x770) {
            *((u8 *)state + 0x7b) |= 8;
            func_ov260_020cd04c(*state, 3);
        }
    }
    {
        int idx = ANG2IDX(state[0x19]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((Vec3 *)(*(int *)(*state + 0x428) + 0x2c), &rot, (Vec3 *)(state + 8));
    if (STAGE(state) >= 2) {
        seg.pos = *(Vec3 *)(*state + 0x74);
        seg.radius = *(int *)(*state + 0x80);
        seg.length = func_01ff8d18((Vec3 *)(state + 8), &seg.axis);
        func_ov260_020cd2a0(state, STAGE(state), 0, 0, &seg);
    } else {
        func_ov260_020cd2a0(state, STAGE(state), 0, 0, 0);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (STAGE(state) >= 2) {
        func_ov107_020c9264(*state, 0x18, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x428), 0xe, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020ce70c);
        return;
    }
    func_ov260_020cd794(node);
    state[0x19] = state[0x1a];
    STAGE(state)++;
    *((u8 *)state + 0x7b) = 0;
    *((u8 *)state + 0x79) = 0;
    func_ov107_020c9264(*state, STAGE(state) * 2 + 0x13, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x428), STAGE(state) * 2 + 9, 0);
    func_ov260_020cd148(*state, (u8)(STAGE(state) == 1 ? 0x17 : 0x1a), state[4]);
}
