/* Companion to func_02031644: the same pair of packed end codes, classified for the other axis. */
int func_02031730(int *p) {
    switch (*p & (int)0xc000c000) {
    case 0x00000000:
    case 0x00008000:
    case 0x40008000:
        return 8;
    case 0x00004000:
    case 0x40000000:
    case (int)0x80008000:
        return 0x10;
    case 0x40004000:
    case (int)0x80000000:
    case (int)0x80004000:
    case (int)0xc0008000:
        return 0x20;
    case (int)0xc0000000:
    case (int)0xc0004000:
        return 0x40;
    }
    return 0;
}
