extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov285_020d20f8(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct ov285_LowByteFlags { unsigned bits : 8; };

/*
 * Enters action 0x48 on the actor.
 *
 * Raises bits 6 and 7 of the actor flag byte and clears bit 1 of it, sets bit 0
 * of the halfword at 0x1ae, clears bit 0 of the flag byte the pose node points
 * at, and clears the elapsed counter.  It then issues the actor request with id
 * 0 and mode 0x48 against the stored handle, and installs the per-frame step in
 * its own slot, so it runs once and replaces itself.
 *
 * Twin of ov286's 020d3e50 down to the instruction; the two overlays differ only
 * in the step they hand over to.
 */
void func_ov285_020d2030(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0xc0) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~2;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct ov285_LowByteFlags *)(*(int *)(*state + 0x38c) + 8))->bits &= ~1;
    state[10] = 0;
    func_ov107_020c5af8(*state, 0, 0x48, state[3]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov285_020d20f8);
}
