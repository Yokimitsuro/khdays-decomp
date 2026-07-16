/* func_ov024_02083c28 -- MobiClip: is the stream at ctx+0x6c ready to deliver data?
 * Mode 0 consults the per-entry ready byte at ctx[0x74][ctx[0x64]]; modes 1..4 are always
 * ready; anything else is not a valid mode. */
int func_ov024_02083c28(int ctx) {
    switch (*(int *)(ctx + 0x6c)) {
    case 0:
        return *(char *)(*(int *)(ctx + 0x74) + *(int *)(ctx + 0x64)) != 0;
    case 1:
    case 2:
    case 3:
    case 4:
        return 1;
    default:
        return 0;
    }
}
