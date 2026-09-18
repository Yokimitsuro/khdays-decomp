/* Leap entry of the ov169 enemy (and its byte-identical twins). With a target in reach the
 * +0x30/+0x38 counters reset, the +0xc velocity becomes the direction to the target scaled by
 * 0x666 and the flight lasts distance/0x666 frames; the +0x3c drop is pre-integrated over half of
 * them (the frame-time inverse times -0x100 accumulates into a falling step), the +0x40 shadow
 * copies the +0x10 height, and a flight shorter than 0xf000 (after the <<12 scaling) rescales the
 * velocity to 0xf000. The +0x18 spin copies the actor's +0x390 vector with a random yaw offset in
 * [-0x165, 0x165]. In every case reaction 0x13f mode 5 fires, the +0x60 flags drop bit 7 and set
 * bit 0 of the high byte, the +0x388 item's +8 low byte sets bit 0, the +0x24 origin copies the
 * +8 position and the tick hands off to the leap state. */
typedef unsigned char u8;

struct Vecx32 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };

extern int func_ov107_020cab14(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern char *OS_IsThreadAvailable_0x020c9848(void);
extern int FX_Inv_0x01ff8a40(int v);
extern int FX_Inv(int a, int b);
extern int func_02023eb4(int bound);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov170_020d086c(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov170_020d0634(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 dir;
    unsigned short *hw;
    unsigned int h;
    int target;
    int step;
    int i;

    target = func_ov107_020cab14(*state, 0);
    if (target != 0) {
        state[0xe] = 0;
        state[0xc] = 0;
        VEC_Subtract((void *)(target + 0x74), (void *)state[2], &dir);
        state[0xd] = func_01ff8d18(&dir, &dir) / 0x666;
        func_01ffa724(0x666, &dir, (void *)(state + 3));
        state[0x10] = state[4];
        state[0xf] = 0;
        i = 0;
        step = 0;
        for (; i < state[0xd] / 2; i++) {
            step += FX_Mul(FX_Inv_0x01ff8a40(*(int *)(OS_IsThreadAvailable_0x020c9848() + 0x40)), -0x100);
            state[0xf] -= step;
        }
        state[0xd] <<= 12;
        if (state[0xd] != 0 && state[0xd] < 0xf000) {
            func_01ffa724(FX_Inv(state[0xd], 0xf000), (void *)(state + 3), (void *)(state + 3));
            state[0x10] = state[4];
            state[0xd] = 0xf000;
        }
        *(struct Vecx32 *)(state + 6) = *(struct Vecx32 *)(*state + 0x390);
        state[7] += func_02023eb4(0x2cb) - 0x165;
    }
    func_ov107_020c5af8(*state, 0x13f, 5, (void *)state[2]);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 1 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
    ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    *(struct Vecx32 *)(state + 9) = *(struct Vecx32 *)state[2];
    *(u8 *)(state + 0x12) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov170_020d086c);
}
