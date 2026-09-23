/* Move entry: bit 7 of the actor's +0x60 high byte clears, the +0x20 heading turns back by the
 * frame rate scaled by -0xd0 / 0x88, the next move is 3 and the node's handler is cleared. */
typedef unsigned short u16;
struct Hw60 { u16 lo : 8; u16 hi : 8; };

extern void func_0203c634(int *node, int slot, void *cb);

void func_ov254_020d3890(int *node)
{
    int *state = (int *)node[1];

    ((struct Hw60 *)(*state + 0x60))->hi &= ~0x80;
    state[8] += *(int *)(node[0] + 0x2c) * -0xd0 / 0x88;
    *(signed char *)(*state + 0x1c7) = 3;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
