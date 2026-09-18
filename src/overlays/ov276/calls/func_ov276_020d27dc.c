/* Descent entry of the ov276 enemy: drops bit 0 of the +0x60 high byte, sets bits 0-1 of
 * +0x1ae, then bits 1/2/7 of the high byte, clears bit 0 of the +0x3ac item's +8 word, fires
 * reaction 0 mode 0x4d at the +0x474 point and hands off to d28a4. */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov276_020d28a4(int *node);

void func_ov276_020d27dc(int *node)
{
    int *state = (int *)node[1];
    unsigned short *hw;
    unsigned int h;

    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    *(unsigned short *)(*state + 0x1ae) |= 3;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    ((struct w8 *)(*(int *)(*state + 0x3ac) + 8))->lo &= ~1;
    func_ov107_020c5af8(*state, 0, 0x4d, (void *)(*state + 0x474));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov276_020d28a4);
}
