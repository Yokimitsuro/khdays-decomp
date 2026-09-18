/* Ascent entry of the ov276 enemy: sets bits 1-2 of the +0x60 high byte and bit 0 of +0x1ae,
 * clears bit 0 of the +0x3ac item's +8 word, sets bit 6 of the high byte, fires reaction 0 mode
 * 0x49 at the +0x474 point, resets the +0x4c timer and hands off to d298c. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov276_020d298c(int *node);

void func_ov276_020d28c4(int *node)
{
    int *state = (int *)node[1];
    unsigned short *hw;
    unsigned int h;

    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct w8 *)(*(int *)(*state + 0x3ac) + 8))->lo &= ~1;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    func_ov107_020c5af8(*state, 0, 0x49, (void *)(*state + 0x474));
    state[0x13] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov276_020d298c);
}
