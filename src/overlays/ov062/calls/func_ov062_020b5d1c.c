#pragma thumb on
/* func_ov062_020b5d1c -- map the entry kind (@obj+0x918) to its icon id, ov062 (byte-identical twin of the ov043 entry-kind map).
 * 0x13/0x14/0x15 -> 0xa7/0xa8/0xa9; anything else -> 0xa6. */
int func_ov062_020b5d1c(char *obj) {
    switch (*(unsigned char *)(obj + 0x918)) {
    case 0x13: return 0xa7;
    case 0x14: return 0xa8;
    case 0x15: return 0xa9;
    }
    return 0xa6;
}
