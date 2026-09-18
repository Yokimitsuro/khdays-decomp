/* Release of the ov220 enemy: sets bits 1-2 and 7 of the +0x60 flag high byte and bit 0 of the
 * +0x1ae halfword, clears bit 0 of the +0x388 item's +8 byte and bit 0 of the flag high byte,
 * and ends the state with sub-state 0. */
typedef unsigned char u8;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };

extern void func_0203c634(int *node, int slot, void *cb);

void func_ov220_020d39c0(int *node)
{
    int *state = (int *)node[1];
    unsigned short *hw;
    unsigned int h;

    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    /* hw60.hi |= 0x86 -- explicit-shift form (bitfield |= adds a redundant mask) */
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
