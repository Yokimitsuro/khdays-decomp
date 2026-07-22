/* func_ov023_02083b94 -- set the low 5 bits of slot `idx`'s mode byte (+0x2a, 0x30 stride).
 * Written as a 5-bit BITFIELD: the ROM's `bics #0x1f` + `and #0x1f` + `orr` pair is what a
 * bitfield store emits; a hand-written mask/or expression is 4 bytes longer because it keeps the
 * masked value in a second register. The slot address is also recomputed for the store rather
 * than cached, which is what the ROM does. */
extern int data_ov023_0208a784;

struct Ov023Slot { unsigned char lo : 5, hi : 3; };

void func_ov023_02083b94(int idx, int v) {
    int base = *(int *)((char *)&data_ov023_0208a784 + 4);
    ((struct Ov023Slot *)(base + idx * 0x30 + 0x2a))->lo = (unsigned char)v;
}
