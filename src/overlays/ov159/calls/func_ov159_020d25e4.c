/* c634 init of the ov158 enemy: reset owner status bytes (+0x1c6=0, +0x1c7=-1), drop bit 0 of
 * the +0x388 item's +8 word, cache owner+0xb0 / owner+0x74 into state[0x13..0x14], raise bits
 * 1-2 of the +0x60 high byte, clear the owner's +0x54 when the current scene is 0x162 (ov002
 * b84c) and arm the three phase callbacks (slots 1/0/2). */
struct bf { unsigned b : 8; };
extern int func_ov002_0206b84c(void);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov159_020d2904(void);
extern void func_ov159_020d26c8(void);
extern void func_ov159_020d2850(void);

void func_ov159_020d25e4(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[0x13] = *state + 0xb0;
    state[0x14] = *state + 0x74;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    if (func_ov002_0206b84c() == 0x162) {
        *(int *)(*state + 0x54) = 0;
    }
    func_0203c634(node, 1, func_ov159_020d2904);
    func_0203c634(node, 0, func_ov159_020d26c8);
    func_0203c634(node, 2, func_ov159_020d2850);
}
