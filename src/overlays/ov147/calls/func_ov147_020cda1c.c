/* Enter the guard pose: set 0x46 in the hw60 high byte, raise bit 0 of the flags at +0x1ae,
 * clear bit 0 of the sub-object's status word at +8, start effect 0x49 anchored on the object's
 * own transform, reset the hold timer and continue in the next step.
 *
 * Matched byte-exact 2026-07-23. The hw60 OR must be the explicit shift expression, NOT the
 * `hi |= K` bitfield: the bitfield form adds a 16-bit truncation (lsl #0x10 / lsr #0x10) that
 * the ROM only has on the AND side.
 *
 * One of four byte-identical siblings. */
extern void func_ov107_020c5af8(int obj, int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov147_020cdabc(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByte32 { unsigned bits : 8; };

void func_ov147_020cda1c(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x46) << 0x18) >> 0x10);
    }
    *(unsigned short *)(state[0] + 0x1ae) |= 1;
    ((struct LowByte32 *)(*(int *)(state[0] + 0x38c) + 8))->bits &= ~1;
    func_ov107_020c5af8(state[0], 0, 0x49, state[0] + 0x74);
    state[0x10] = 0;
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov147_020cdabc);
}
