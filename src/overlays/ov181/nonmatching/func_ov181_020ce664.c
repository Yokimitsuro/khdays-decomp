/* NONMATCHING: equivalent C, single-instruction scheduler tie (count=6, 228B).
 * Byte-exact EXCEPT the placement of `bic lr, lr, #0xff00` (the `x & ~0xff00`
 * low-byte-keep of the hw60 config): the original issues it LATE (right before
 * the final orr), mwcc issues it EARLY (after the first lsl of the high-byte
 * chain). x lands in lr both ways (ip/callback/this are pre-live); purely the
 * list-scheduler slotting the independent bic into the dependent shift chain.
 * No C reorder (hb temp, lo temp, operand swap, inline) moves it.
 * NOTE: the 64-bit fixed-point scale MATCHED -- `holder->0x7c -= (int)((((long
 * long)m << 7) + 0x800) >> 12)` with m = (*this)->0x2c * 0x1e reproduces the
 * mul/asr/adds/adc/lsr/orr lowering exactly (un-defers the fixed-point class).
 * Semantics: copy Vec3 holder+0x78->holder+0x54; holder->0x7c -= scale; guard
 * node->0x17a bit0 else return; func_ov107_020c9264(node,0x12,0); func_ov107_
 * 020c9ee8((*holder)->0x390,0,0); hw60 node->0x60 hi-byte &= ~0x40; holder->
 * 0x6c=0; holder->0x51 &= ~2; advance(this,(s8)0x20, func_ov181_020ce748). */
extern int func_ov107_020c9264();
extern int func_ov107_020c9ee8();
extern int func_0203c634();
extern int func_ov181_020ce748();

struct Vec3 { int x, y, z; };

void func_ov181_020ce664(int this_) {
    int holder = *(int *)(this_ + 4);
    int node;
    int m;
    unsigned int x;

    *(struct Vec3 *)(holder + 0x54) = *(struct Vec3 *)(holder + 0x78);

    m = *(int *)(*(int *)this_ + 0x2c) * 0x1e;
    *(int *)(holder + 0x7c) -= (int)((((long long)m << 7) + 0x800) >> 12);

    node = *(int *)holder;
    if (((unsigned)(*(unsigned char *)(node + 0x17a) << 31) >> 31) == 0) return;

    func_ov107_020c9264(node, 0x12, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)holder + 0x390), 0, 0);

    node = *(int *)holder;
    x = *(unsigned short *)(node + 0x60);
    {
        unsigned int hb =
            (((unsigned int)(unsigned short)(((x << 16) >> 24) & ~0x40)) << 24) >> 16;
        *(unsigned short *)(node + 0x60) = (x & ~0xff00) | hb;
    }
    *(int *)(holder + 0x6c) = 0;
    *(unsigned char *)(holder + 0x51) &= ~2;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), func_ov181_020ce748);
}
