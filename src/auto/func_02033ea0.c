/* True when the 32-byte slot selected by the top byte of `handle` is live (halfword at
 * +0x14), its stored id at +0x18 matches the handle's low 24 bits, and its payload flag at
 * +0x1c is set.  Companion of func_02033e00.
 *
 * Both failure paths share one `return 0`, so they reach it with a goto. */
extern char *data_0204c234;

int func_02033ea0(unsigned int handle) {
    char *rec = data_0204c234 + 0xb44e4 + (handle >> 24) * 32;
    if (*(unsigned short *)(rec + 0x14) == 0) {
        goto no;
    }
    if (*(unsigned int *)(rec + 0x18) != (handle & 0xffffff)) {
        goto no;
    }
    return *(int *)(rec + 0x1c) != 0;
no:
    return 0;
}
