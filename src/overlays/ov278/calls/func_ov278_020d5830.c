/* Rider release (second rider): raises flags 0xc2 and clears bit 0 in the actor's +0x60 high
 * byte, sets bits 0-1 of +0x1ae, clears bit 0 of the +0x3c0 / +0x3c4 items' +8 low byte and bit
 * 0 of +0x3d4, then dispatches null. */
typedef unsigned short u16;
struct b8 { unsigned f : 8; };
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov278_020d5830(int *node)
{
    int *state = (int *)node[1];
    unsigned short *hw;
    unsigned int h;

    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0xc2) << 0x18) >> 0x10);
    {
        int actor = *state;
        u16 w = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (w & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)w << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    *(unsigned short *)(*state + 0x100 + 0xae) |= 3;
    ((struct b8 *)(*(int *)(*state + 0x3c0) + 8))->f &= ~1;
    ((struct b8 *)(*(int *)(*state + 0x3c4) + 8))->f &= ~1;
    *(int *)(*state + 0x3d4) &= ~1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
