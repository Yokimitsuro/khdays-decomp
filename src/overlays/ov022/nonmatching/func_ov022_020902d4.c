/* NONMATCHING: tail-merge tie. Original duplicates the `*p |= 0x80` in BOTH the
 * equal branch (predicated, orreq;strheq;bxeq) and the not-equal fallthrough,
 * i.e. it does NOT factor. mwcc always tail-merges the common `|= 0x80` into a
 * single unconditional tail (predicating the store/byte instead), yielding a
 * shorter body. Tried equal-first and not-equal-first structures; both merge.
 * Semantics: if field@+0xc changed, write it and set byte@+2=1; always set
 * flag bit 7 of *arg0. */
void func_ov022_020902d4(unsigned short *arg0, int arg1) {
    if (*(int *)(arg0 + 6) == arg1) {
        *arg0 |= 0x80;
        return;
    }
    *(int *)(arg0 + 6) = arg1;
    *(char *)(arg0 + 1) = 1;
    *arg0 |= 0x80;
}
