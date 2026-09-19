/* Dash tick of the ov221 enemy. The +0x20 velocity decays per 0x88 slice of the frame by
 * 1.0 - 0x500 x (slice / 0x88) and becomes the +0x14 step; the +0x5c timer accumulates the
 * rate and once (+0x75 bit 2) past 0x2420 fires reaction 0x14b mode 0x11 at the +8 point when
 * there is no +0x78 target. Once the +4 item goes idle (+0xad): without a target sub-state 2
 * ends the state; with one, a grounded owner (+0x17a bit 0) plays animation 0x17, sends the
 * zero-vector mode-0xa message with flag 3 and hands over to func_ov225_020d353c, otherwise
 * sub-state 6 ends the state. While busy, a step shorter than 0x80 does nothing; otherwise
 * sub-action 2 (target) or 4 runs (func_ov225_020d0a08). */
typedef struct { int x, y, z; } Vec3;
struct Bit0 { unsigned char bit0 : 1; };

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int FX_Inv(int num, int den);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 v, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern int VEC_Mag(const Vec3 *v);
extern void func_ov225_020d0a08(int *state, int action, int arg);
extern Vec3 data_02041dc8;
extern void func_ov225_020d353c(int *node);

void func_ov225_020d3354(int *node)
{
    int *state = (int *)node[1];
    int rem;
    int step;

    for (rem = *(int *)(node[0] + 0x2c); rem > 0; rem -= 0x88) {
        step = rem <= 0x88 ? rem : 0x88;
        func_01ffa724(0x1000 - FX_Mul(FX_Inv(step, 0x88), 0x500), (Vec3 *)(state + 8), (Vec3 *)(state + 8));
    }
    *(Vec3 *)(state + 5) = *(Vec3 *)(state + 8);
    state[0x17] += *(int *)(node[0] + 0x2c);
    if ((*(unsigned char *)((char *)state + 0x75) & 4) == 0 && state[0x17] >= 0x2420) {
        if (state[0x1e] == 0) {
            func_ov107_020c5af8(*state, 0x14b, 0x11, (void *)state[2]);
        }
        *(unsigned char *)((char *)state + 0x75) |= 4;
    }
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        if (state[0x1e] != 0) {
            if (((struct Bit0 *)(*state + 0x17a))->bit0 != 0) {
                func_ov107_020c9264(*state, 0x17, 0);
                func_ov107_020c0b90(*state, 0xa, data_02041dc8, 3);
                func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov225_020d353c);
                return;
            }
            *(unsigned char *)(*state + 0x1c7) = 6;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (VEC_Mag((Vec3 *)(state + 5)) < 0x80) {
        return;
    }
    func_ov225_020d0a08(state, state[0x1e] != 0 ? 2 : 4, 0);
}
