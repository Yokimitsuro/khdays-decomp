/* Sub-item release step of the ov202 enemy (x2: ov202/203): mirrors the actor's +0x1c4 bit 1
 * into bit 1 of the +4 sub-item's +0x5c flags and, unless the actor is in sub-state 0xa, sets the
 * sub-item states 2->1 and 0->2 and advances to func_ov203_020d67b0. */
struct Bits5c { unsigned b0 : 1, b1 : 1; };

extern void func_0203b9fc(int obj, int slot, int a, int b);
extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov203_020d67b0(void);

void func_ov203_020d6724(int *node) {
    int *state = (int *)node[1];

    ((struct Bits5c *)(state[1] + 0x5c))->b1 = (*(unsigned char *)(*state + 0x1c4) & 2) != 0;
    if (*(signed char *)(*state + 0x310) == 0xa) {
        return;
    }
    func_0203b9fc(state[1], 2, 1, 0);
    func_0203b9fc(state[1], 0, 2, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov203_020d67b0);
}
