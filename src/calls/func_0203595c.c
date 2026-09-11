/* Record `a`'s entry-count cap: 6 plus twice a per-record lookup value (param 0x5a
 * into func_020358f4), clamped to 18 -- the stride-4 array at +0xba only has room
 * for 18 entries. */
extern int func_020358f4(int a, int b);

int func_0203595c(int a) {
    unsigned char n = 6;
    n += func_020358f4(a, 0x5a) * 2;
    if (n > 18)
        n = 18;
    return n;
}
