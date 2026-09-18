/* func_ov245_020d70b0 -- finish entry: clears bit 0 then raises bits 1, 2 and 7 of the actor's
 * +0x60 high byte, clears bit 0 of the +0x388 item's +8 low byte, spawns effect 0 at the state's
 * +0xc position (020c0b90, flag 1), fires reaction 0x49 there (020c5af8), requests sub-state 0
 * and releases the node's slot. */
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c0b90(int actor, int effect, Vec3 v, int flag);
extern void func_ov107_020c5af8(int actor, int a, int id, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov245_020d70b0(int *node) {
    int *state = (int *)node[1];

    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x86) << 0x18) >> 0x10);
    }
    ((struct w8 *)(*(int *)(*state + 0x388) + 8))->lo &= ~1;
    func_ov107_020c0b90(*state, 0, *(Vec3 *)state[3], 1);
    func_ov107_020c5af8(*state, 0, 0x49, (void *)state[3]);
    *(unsigned char *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
