/*
 * Set or clear the three action flags on the 64-bit field at +0, depending on the argument.
 *
 * The park concluded this was "not reproducible without the original header's 0-valued flag
 * macros", reading the ROM's `*arg0 = *arg0` as a no-op self-store and the repeated
 * `arg0[1] = v` as redundant stores that -O4 would remove.  They are the untouched halves of
 * three 64-bit operations.
 *
 * Note where the masks live: 0x2000 sits in the HIGH half, so the constant is
 * `0x2000LL << 32` = 0x200000000000.  Getting that wrong gives `orr r2, r1, #2` instead of
 * `orr r2, r1, #0x2000` and costs 4 bytes -- the high-half mask has to be shifted, not just
 * written as a long long.
 */
void func_ov022_020ad838(unsigned int *arg0, int arg1) {
    if (arg1 != 0) {
        *(unsigned short *)(arg0 + 6) = 0;
        *(unsigned short *)((int)arg0 + 0x1a) = 0;
        *(long long *)arg0 |= 0x200000000000LL;
        *(long long *)arg0 |= 0x80000;
        *(long long *)arg0 |= 0x80;
        return;
    }
    *(long long *)arg0 &= ~0x200000000000LL;
    *(long long *)arg0 &= ~0x80000LL;
    *(long long *)arg0 &= ~0x80LL;
}
