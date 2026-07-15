#pragma thumb on
/* func_ov043_020b351c -- map the entry kind (@obj+0x918) to its icon id, ov043.
 * 0x13/0x14/0x15 -> 0xa7/0xa8/0xa9; anything else -> 0xa6. */
int func_ov043_020b351c(char *obj) {
    switch (*(unsigned char *)(obj + 0x918)) {
    case 0x13: return 0xa7;
    case 0x14: return 0xa8;
    case 0x15: return 0xa9;
    }
    return 0xa6;
}
