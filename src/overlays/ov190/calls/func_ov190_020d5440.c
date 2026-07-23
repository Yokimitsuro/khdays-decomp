/* Enter the wind-down: play animation 7, stop the sub-effect at +0x3c0, set 0x40 in the hw60
 * high byte, clear the travel accumulator and continue in the next step.
 *
 * Matched byte-exact 2026-07-23, first compile. One of three byte-identical siblings. */
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_ov107_020c9ee8(int p, int a, int b);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov190_020d54b4(void);

void func_ov190_020d5440(int *node) {
    int *state = (int *)node[1];

    func_ov107_020c9264(state[0], 7, 0);
    func_ov107_020c9ee8(*(int *)(state[0] + 0x3c0), 1, 0);
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    state[6] = 0;
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov190_020d54b4);
}
