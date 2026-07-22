/* func_ov023_020830cc -- raise the "closing" bit (8) of the ov023 status halfword at +0x8758c,
 * but only when it is not already set and func_02034014 reports no work outstanding. Always
 * reports 0 (stay in this state). The scene root is re-read from the global for the store. */
extern int func_02034014(int a);
extern int data_ov023_0208a784;

int func_ov023_020830cc(void) {
    if ((*(unsigned short *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x8758c) & 8) == 0 &&
        func_02034014(0) == 0) {
        *(unsigned short *)(*(int *)((char *)&data_ov023_0208a784 + 4) + 0x8758c) |= 8;
    }
    return 0;
}
