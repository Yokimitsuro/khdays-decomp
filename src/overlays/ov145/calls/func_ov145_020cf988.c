/* Retreat entry of the ov144 enemy (and its byte-identical twin): sets bits 1-2 of the +0x60
 * flag high byte, bit 0 of the +0x1ae halfword and bit 6 of the flag high byte, publishes the
 * +0x74 position with mode 0, zeroes the +0x38 clock and hands off to the retreat tick. */
struct Vecx32 { int x, y, z; };

extern void func_ov107_020c0b90(int actor, int a, struct Vecx32 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov145_020cfa44(int *node);

void func_ov145_020cf988(int *node)
{
    int *state = (int *)node[1];
    unsigned short *hw;
    unsigned int h;

    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 6 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    *(unsigned short *)(*state + 0x1ae) |= 1;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    func_ov107_020c0b90(*state, 0, *(struct Vecx32 *)(*state + 0x74), 0);
    state[0xe] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov145_020cfa44);
}
