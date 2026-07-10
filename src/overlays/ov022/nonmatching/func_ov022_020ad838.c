/*
 * [nonmatching: dead self-store + repeated-store pattern]
 *
 * Sets/clears a group of flags in the two words at arg0[0]/arg0[1] depending on
 * arg1. The original emits `*arg0 = *arg0` (a no-op OR with a build-time 0 flag)
 * before each real bit op, and re-writes arg0[1] = v after each — redundant
 * stores mwcc's -O4 dead-store elimination removes (any literal `| 0` folds, and
 * identical consecutive stores collapse). Not reproducible without the original
 * header's 0-valued flag macros; left uncarved (byte-exact in the blob).
 */
void func_ov022_020ad838(unsigned int *arg0, int arg1) {
    unsigned int v;
    if (arg1 != 0) {
        *(unsigned short *)(arg0 + 6) = 0;
        *(unsigned short *)((int)arg0 + 0x1a) = 0;
        v = arg0[1] | 0x2000;
        arg0[1] = v;
        *arg0 |= 0x80000;
        arg0[1] = v;
        *arg0 |= 0x80;
        arg0[1] = v;
        return;
    }
    v = arg0[1] & 0xffffdfff;
    arg0[1] = v;
    *arg0 &= 0xfff7ffff;
    arg0[1] = v;
    *arg0 &= 0xffffff7f;
    arg0[1] = v;
}
