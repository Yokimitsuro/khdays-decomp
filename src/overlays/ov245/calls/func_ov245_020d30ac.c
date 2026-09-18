/* func_ov245_020d30ac -- slide entry: flags the actor's +0x38c, spawns effect 0 at the state's +8
 * position (020c0b90), fires reaction 0x15a of kind 4 there (020c5af8), keeps the position at
 * +0x38, clears +0x44/+0x4c/+0x24, raises bit 0 of the +0x60 high byte and bit 0 of the +0x388
 * item's +8 low byte, scales the +0x18 direction by 1.1 into the +0xc velocity and moves the
 * node to 020d31a4. */
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d31a4(void);

void func_ov245_020d30ac(int *node) {
    int *state = (int *)node[1];

    *(int *)(*state + 0x38c) = 1;
    func_ov107_020c0b90(*state, 0, *(Vec3 *)state[2], 0);
    func_ov107_020c5af8(*state, 0x15a, 4, (void *)state[2]);
    *(Vec3 *)(state + 0xe) = *(Vec3 *)state[2];
    state[0x11] = 0;
    state[0x13] = 0;
    state[9] = 0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo |= 1;
    func_01ffa724(0x11a0, (Vec3 *)(state + 6), (Vec3 *)(state + 3));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d31a4);
}
