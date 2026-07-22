/* Message hook: only while the owner's state byte at +0x1c6 is 1 and the message carries
 * both bit 0 and bit 4, moves the sub-state at +0x1c7 to 2 and reports handled.
 *
 * All three failure paths share one `return 0`, reached with a goto -- written as inline
 * early returns mwcc duplicates the epilogue. */
int func_ov245_020d3d14(char *self, int unused, unsigned int *msg) {
    char *o = *(char **)(*(char **)(self + 0x214));
    unsigned short m;
    if (*(signed char *)(o + 0x1c6) != 1) {
        goto no;
    }
    m = (unsigned short)*msg;
    if ((m & 1) == 0) {
        goto no;
    }
    if ((m & 0x10) == 0) {
        goto no;
    }
    o[0x1c7] = 2;
    return 1;
no:
    return 0;
}
