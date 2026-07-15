/* func_ov105_020bd4dc -- clear the low request bit of the shared control word @0x027fff96,
 * ov105 (only if set). */
void func_ov105_020bd4dc(void) {
    unsigned short *p = (unsigned short *)0x027fff96;
    if (*p & 1) {
        *p &= ~1;
    }
}
