/* Reset the AI state block and install the three step callbacks: clear the action bytes at
 * +0x1c6/+0x1c7, drop bit 0 of the sub-object's byte at +8, point state[2] at the object's
 * own transform (+0x74) and state[0x13] at the hit flag inside the component at +0x384, set
 * 0x06 in the hw60 high byte, then register the tick, the reaction and the finish step.
 *
 * Matched byte-exact 2026-07-23, first compile. One of three byte-identical siblings. */
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov293_020d244c(void);
extern void func_ov293_020d2204(void);
extern void func_ov293_020d237c(void);

struct LowByte { unsigned bits : 8; };

void func_ov293_020d213c(int *node) {
    int *state = (int *)node[1];

    *(char *)(state[0] + 0x1c6) = 0;
    *(char *)(state[0] + 0x1c7) = -1;
    ((struct LowByte *)(*(int *)(state[0] + 0x388) + 8))->bits &= ~1;
    state[2] = state[0] + 0x74;
    state[0x13] = *(int *)(state[0] + 0x384) + 0xad;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    }
    func_0203c634(node, 1, func_ov293_020d244c);
    func_0203c634(node, 0, func_ov293_020d2204);
    func_0203c634(node, 2, func_ov293_020d237c);
}
