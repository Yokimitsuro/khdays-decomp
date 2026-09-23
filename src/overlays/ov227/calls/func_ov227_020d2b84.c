/* Charge wind-up tick of the ov227 enemy. Losing the target (ov227 14bc below zero) ends the
 * action outright. The +0x5c timer accumulates the owner's rate; once it passes 0x1320 with a
 * +0x78 target or 0x1100 without, reaction 0x14d fires at the +8 point in mode 6 (7 without
 * a target, followed by mode 5) and bit 0 of +0x75 is set; past 0x660 mode 5 fires once more
 * (bit 1). While the +4 owner's +0xad byte is set the tick waits. Then animation 9 (0xd without
 * a target) plays in mode 1, the unit direction from the +8 point to the +0x3e8 player's +0x190
 * is taken, the +0x20 velocity is the sine/cosine of the +0x50 heading (y from that direction)
 * scaled 0.75, +0x58 keeps the heading, the +0x3b0 body raises bit 0 of its +8 low byte, the
 * owner is sent mode 3 (4 without a target) with the zero vector, +0x60 keeps the timer and
 * the tick hands over to func_ov227_020d2e00. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

struct Byte8 { unsigned int lo : 8, rest : 24; };

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

extern int func_ov227_020d14bc(int *node, Vec3 *dir);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c5af8(int owner, int id, u16 mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 v, int flag);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;
extern void func_ov227_020d2e00(int *node);

void func_ov227_020d2b84(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    unsigned short idx;
    int mode;

    if (func_ov227_020d14bc(node, 0) < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x17] += *(int *)(node[0] + 0x2c);
    if ((*(u8 *)((char *)state + 0x75) & 1) == 0) {
        if ((state[0x1e] != 0 && state[0x17] >= 0x1320) || (state[0x1e] == 0 && state[0x17] >= 0x1100)) {
            func_ov107_020c5af8(*state, 0x14d, state[0x1e] != 0 ? 6 : 7, (void *)state[2]);
            if (state[0x1e] == 0) {
                func_ov107_020c5af8(*state, 0x14d, 5, (void *)state[2]);
            }
            *(u8 *)((char *)state + 0x75) |= 1;
        }
    }
    if ((*(u8 *)((char *)state + 0x75) & 2) == 0 && state[0x17] >= 0x660) {
        func_ov107_020c5af8(*state, 0x14d, 5, (void *)state[2]);
        *(u8 *)((char *)state + 0x75) |= 2;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, state[0x1e] != 0 ? 9 : 0xd, 1);
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x3e8) + 0x190), (Vec3 *)state[2], &d);
    func_01ff8d18(&d, &d);
    idx = FX_RadToIdx(state[0x14]);
    state[8] = data_0203d210[(idx >> 4) * 2];
    state[9] = 0;
    state[0xa] = data_0203d210[(idx >> 4) * 2 + 1];
    state[9] = d.y;
    state[0x16] = state[0x14];
    func_01ffa724(0xc00, (Vec3 *)(state + 8), (Vec3 *)(state + 8));
    ((struct Byte8 *)(*(int *)(*state + 0x3b0) + 8))->lo |= 1;
    mode = state[0x1e] != 0 ? 3 : 4;
    func_ov107_020c0b90(*state, mode, data_02041dc8, 0);
    state[0x18] = state[0x17];
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov227_020d2e00);
}
