extern int func_020235d0(int arg0, int arg1);

int func_ov025_02089dac(int entry, unsigned int value) {
    int kind;

    if (*(unsigned char *)(entry + 0x23) != 0) return 0;
    if (*(unsigned short *)(entry + 6) > value) return 0;
    if (*(unsigned short *)(entry + 8) < value) return 0;

    kind = *(unsigned char *)(entry + 0x15);
    if (kind != 0) {
        int enabled;
        kind--;
        kind = (int)((char *)0 + kind);
        kind = (unsigned int)(kind << 0x10) >> 0xf;
        kind += 0x379f;
        enabled = (unsigned int)func_020235d0(kind, 2) >= 1;
        if (enabled == 0) return 0;
    }

    return 1;
}
