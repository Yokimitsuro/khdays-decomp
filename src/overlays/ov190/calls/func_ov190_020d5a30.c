/* Enter the charge stance: set 0x06 and then, after the sub-object is disarmed, 0x40 in the
 * hw60 high byte; raise bit 0 of the flags at +0x1ae, clear bit 0 of the status word at +8 of
 * the component at +0x388, start effect 0x49 anchored on the object's own transform and reset
 * the travel accumulator.
 *
 * Matched byte-exact 2026-07-23, first compile. Both hw60 ORs are the explicit shift
 * expression: the `hi |= K` bitfield form adds a 16-bit truncation the ROM does not have.
 *
 * One of four byte-identical siblings. */
extern void func_ov107_020c5af8(int obj, int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov190_020d5af4(void);

struct LowByte32 { unsigned bits : 8; };

void func_ov190_020d5a30(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    }
    *(unsigned short *)(state[0] + 0x1ae) |= 1;
    ((struct LowByte32 *)(*(int *)(state[0] + 0x388) + 8))->bits &= ~1;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c5af8(state[0], 0, 0x49, state[0] + 0x74);
    state[6] = 0;
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov190_020d5af4);
}
