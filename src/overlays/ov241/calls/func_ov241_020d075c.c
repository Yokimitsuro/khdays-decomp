/* Latch the "hurt" flag on the object and on its three parts, then hand off to the next
 * AI step: set 0x86 in the high byte of the hw60 flags word, and OR bit 1 into +0x5c of
 * each of the three part objects listed at +0x38c.
 *
 * The part is read as `((int *)obj)[i + 0xe3]`, with the 0x38c byte offset FOLDED INTO
 * THE INDEX. Written as `*(int *)(obj + i * 4 + 0x38c)` mwcc strength-reduces the loop
 * to a running byte offset and grows the frame by 8 bytes; with the constant inside the
 * subscript it recomputes `obj + i*4` every iteration, as the ROM does. */
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov241_020d07c4(void);

void func_ov241_020d075c(int *node) {
    int *state = (int *)node[1];
    int i = 0;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    }
    do {
        int part = ((int *)state[0])[i + 0xe3];
        *(int *)(part + 0x5c) |= 2;
        i++;
    } while (i < 3);
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov241_020d07c4);
}
