/* Recoil tick. If bit 0 of the flags at +0x3cc is set the recoil is over: switch the action
 * byte to 8 and drop the think callback. Otherwise wait for the counter at state[0x1a], then
 * latch the stored direction (state[9] -> state[0xf]), reset the step to 1.0, clear the 0x40
 * bit of the hw60 high byte and the counter at state[0xc], and continue in 020cfed8.
 *
 * The bit-0 test is a SIGNED one-bit bitfield: that is what gives `lsl #0x1f ; asrs #0x1f`
 * instead of an `ands #1`. The hw60 clear keeps the extra `(unsigned short)` truncation in
 * the middle of the byte round-trip -- without it the two shifts at 0x10 disappear. */
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov164_020d1cf8(void);

typedef struct { int b0 : 1; } Ov164Bit0;
typedef struct { int x, y, z; } VecFx32;

void func_ov164_020d1c4c(int *node) {
    int *state = (int *)node[1];

    if (((Ov164Bit0 *)(state[0] + 0x3cc))->b0) {
        *(char *)(state[0] + 0x1c7) = 8;
        func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    if (state[0x1a] == 0) {
        return;
    }
    *(VecFx32 *)(state + 0xf) = *(VecFx32 *)(state + 9);
    state[0x10] = 0;
    state[0xe] = 0x1000;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw60 << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    state[0xc] = 0;
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov164_020d1cf8);
}
