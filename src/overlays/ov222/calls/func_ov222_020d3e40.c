/* Retreat tick of the ov221 enemy. The +0x78 target clears and the +0x5c timer accumulates
 * the owner's rate. Outside sub-state 0xd bit 6 of the owner's +0x60 high byte clears, the
 * +0x14 step becomes (0, +0x6c - 0x90, 0) while +0x6c sinks by 0x90 per 0x88 of rate, reaction
 * 0x12a fires mode 0xf at 0x1a90 and mode 4 at 0xaa0 at the +8 point (bits 0/1 of +0x75), and
 * at 0x1a90 with the owner grounded (+0x17a bit 0) the owner is sent mode 9 with the zero
 * vector (bit 2). In sub-state 0xd the same step and sink apply, at 0xdd0 with the owner
 * grounded reaction mode 0x10 fires and mode 9 is sent (bit 0), and at 0x1980 mode 7 is sent
 * (bit 1). Once the +4 owner's +0xad byte clears sub-state 2 is requested -- 0xc from sub-state
 * 0xd in game mode 2 -- and the action ends. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b1 { unsigned char b0 : 1; };
static inline void VEC_Set(Vec3 *v, int x, int y, int z) { v->x = x; v->y = y; v->z = z; }

extern void func_ov107_020c5af8(int actor, int id, int mode, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 v, int flag);
extern int func_ov002_0207298c(void);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;

void func_ov222_020d3e40(int *node)
{
    int *state = (int *)node[1];

    state[0x1e] = 0;
    state[0x17] += *(int *)(*node + 0x2c);
    if (*(signed char *)(*state + 0x1c6) != 0xd) {
        ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
        VEC_Set((Vec3 *)(state + 5), 0, state[0x1b] - 0x90, 0);
        state[0x1b] += *(int *)(*node + 0x2c) * -0x90 / 0x88;
        if ((*(u8 *)((char *)state + 0x75) & 1) == 0 && state[0x17] >= 0x1a90) {
            *(u8 *)((char *)state + 0x75) |= 1;
            func_ov107_020c5af8(*state, 0x12a, 0xf, (void *)state[2]);
        }
        if ((*(u8 *)((char *)state + 0x75) & 2) == 0 && state[0x17] >= 0xaa0) {
            *(u8 *)((char *)state + 0x75) |= 2;
            func_ov107_020c5af8(*state, 0x12a, 4, (void *)state[2]);
        }
        if ((*(u8 *)((char *)state + 0x75) & 4) == 0 && state[0x17] >= 0x1a90
            && ((struct b1 *)(*state + 0x17a))->b0 != 0) {
            *(u8 *)((char *)state + 0x75) |= 4;
            func_ov107_020c0b90(*state, 9, data_02041dc8, 1);
        }
    } else {
        VEC_Set((Vec3 *)(state + 5), 0, state[0x1b] - 0x90, 0);
        state[0x1b] += *(int *)(*node + 0x2c) * -0x90 / 0x88;
        if ((*(u8 *)((char *)state + 0x75) & 1) == 0 && state[0x17] >= 0xdd0
            && ((struct b1 *)(*state + 0x17a))->b0 != 0) {
            *(u8 *)((char *)state + 0x75) |= 1;
            func_ov107_020c5af8(*state, 0x12a, 0x10, (void *)state[2]);
            func_ov107_020c0b90(*state, 9, data_02041dc8, 1);
        }
        if ((*(u8 *)((char *)state + 0x75) & 2) == 0 && state[0x17] >= 0x1980) {
            *(u8 *)((char *)state + 0x75) |= 2;
            func_ov107_020c0b90(*state, 7, data_02041dc8, 0);
        }
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    if (func_ov002_0207298c() == 2 && *(signed char *)(*state + 0x1c6) == 0xd) {
        *(u8 *)(*state + 0x1c7) = 0xc;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
