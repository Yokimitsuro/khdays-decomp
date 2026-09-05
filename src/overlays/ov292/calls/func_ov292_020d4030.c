/* Enters the actor's chase behaviour: clears the requested state, drops the
 * primary model's first flag bit, points the sub-state at the owner's two
 * vectors, raises bits 1 and 2 of the flag byte at +0x61, zeroes the working
 * transform and copies it into the shadow slot, then registers the three step
 * callbacks. Same routine as the matched ov178 entry, with a second vector
 * pointer where that one stores a null. */
struct bf { unsigned b : 8; };
struct blk16 { int a, b, c, d; };
extern void func_0202ea34(void *p, int a, int b, int c, int d);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov292_020d4124(void);
extern void func_ov292_020d4324(void);
extern void func_ov292_020d42b8(void);
void func_ov292_020d4030(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = 0xff;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[2] = *state + 0xb0;
    state[3] = *state + 0x74;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0202ea34(state + 0xe, 0, 0, 0, 0);
    *(struct blk16 *)(state + 0x12) = *(struct blk16 *)(state + 0xe);
    func_0203c634(node, 0, func_ov292_020d4124);
    func_0203c634(node, 1, func_ov292_020d4324);
    func_0203c634(node, 2, func_ov292_020d42b8);
}
