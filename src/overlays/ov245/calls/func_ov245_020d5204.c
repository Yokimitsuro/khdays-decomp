/* func_ov245_020d5204 -- landing entry: raises bit 1 of the actor's +0x60 high byte, plays pose 2,
 * spawns effect 1 at the state's +8 position (020c0b90), fires reaction 0x15a of kind 0xc there
 * (020c5af8), clears the actor's +0x3b0 byte, the state's +0x10 byte and +0xc, and moves the
 * node to 020d52b8. */
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov245_020d52b8(void);

void func_ov245_020d5204(int *node) {
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 2, 0);
    func_ov107_020c0b90(*state, 1, *(Vec3 *)state[2], 0);
    func_ov107_020c5af8(*state, 0x15a, 0xc, (void *)state[2]);
    *(unsigned char *)(*state + 0x3b0) = 0;
    *(unsigned char *)((char *)state + 0x10) = 0;
    state[3] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov245_020d52b8);
}
