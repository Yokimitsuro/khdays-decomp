/* func_ov253_020cde74 -- volley tick: the nearest visible target facing the +0xc heading within
 * 60.0 (020cd0d8) is kept at +0x24; with one, the +0x10 heading turns towards it and the +0x1c
 * timer runs up: past 0.167 the first idle +0x45c part (bit 0 of its +0x60 low byte clear) is
 * launched from the +0x39c joint towards the target (020d3a30), reaction 0x16b/5 fires there,
 * the timer restarts and the +0x20 count grows. The +0x14 speed follows three times the frame
 * step (30 / 10); without a target or after eight launches the +0x38c item's +0xa8 flag clears
 * and the node moves to 020ce0ac. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_ov253_020cd0d8(int self, const Vec3 *pos, const Vec3 *dir, int minDot, int maxDist);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_020050b4(int y, int x);
extern void func_ov253_020d3a30(int part, void *anchor, Vec3 *dir);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern void func_ov253_020ce0ac(void);

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void func_ov253_020cde74(int *node) {
    int *state = (int *)node[1];
    Vec3 launch;
    Vec3 aim;
    Vec3 dir;
    int i;

    launch.x = data_0203d210[(FX_RadToIdx(state[3]) >> 4) << 1];
    launch.y = 0;
    launch.z = data_0203d210[((FX_RadToIdx(state[3]) >> 4) << 1) + 1];
    state[9] = func_ov253_020cd0d8(*state, (Vec3 *)state[2], &launch, -0x1000, 0x3c000);
    if (state[9] != 0) {
        VEC_Subtract((Vec3 *)(state[9] + 0x74), (Vec3 *)(*(int *)(*state + 0x39c) + 0x14), &dir);
        func_01ff8d18(&dir, &dir);
        VEC_Subtract((Vec3 *)(state[9] + 0x74), (Vec3 *)state[2], &aim);
        aim.y = 0;
        state[4] = func_020050b4(aim.x, aim.z);
        state[7] += *(int *)(node[0] + 0x2c);
        if (state[7] >= 0x2aa) {
            func_01ff8d18(&aim, &aim);
            for (i = 0; i < 8; i++) {
                if ((((struct hw60 *)((*(int **)(*state + 0x45c))[i] + 0x60))->lo & 1) == 0) {
                    state[7] = 0;
                    func_ov253_020d3a30((*(int **)(*state + 0x45c))[i], (void *)(*(int *)(*state + 0x39c) + 0x14), &dir);
                    func_ov107_020c5af8(*state, 0x16b, 5, (void *)(*(int *)(*state + 0x39c) + 0x14));
                    state[8] += 1;
                    break;
                }
            }
        }
    }
    state[5] = *(int *)(node[0] + 0x2c) * 0x1e / 10;
    if (state[9] != 0 && state[8] < 8) {
        return;
    }
    *(unsigned char *)(*(int *)(*state + 0x38c) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020ce0ac);
}
