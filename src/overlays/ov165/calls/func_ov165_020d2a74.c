/* Enter the recovery stance: set 0x82 in the hw60 high byte and drop 0x0c from it, raise bit 0
 * of the flags at +0x1ae, clear bit 0 of the status word at +8 of the component at +0x388, clear
 * the counter at state[0xc] and start effect 0x48 on the anchor at state[0x14].
 *
 * Matched byte-exact 2026-07-23. One of three byte-identical siblings. */
extern void func_ov107_020c5af8(int obj, int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov165_020d2b3c(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByte32 { unsigned bits : 8; };

void func_ov165_020d2a74(int *node) {
    int *state = (int *)node[1];

    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(state[0] + 0x60))->hi &= ~0xc;
    *(unsigned short *)(state[0] + 0x1ae) |= 1;
    ((struct LowByte32 *)(*(int *)(state[0] + 0x388) + 8))->bits &= ~1;
    state[0xc] = 0;
    func_ov107_020c5af8(state[0], 0, 0x48, state[0x14]);
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov165_020d2b3c);
}
