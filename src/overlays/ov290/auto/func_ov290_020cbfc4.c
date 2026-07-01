void func_ov290_020cbfc4(char *p) {
    *(int *)(p + 0x70) = 0x800;
    *(int *)(p + 0x64) = 0;
    *(int *)(p + 0x68) = 0x800;
    *(int *)(p + 0x6c) = 0;
    {
        unsigned int v = *(unsigned short *)(p + 0x60);
        unsigned int hi = ((v << 16) >> 24) | 6;
        v &= ~0xff00u;
        *(unsigned short *)(p + 0x60) = v | ((hi << 24) >> 16);
    }
}
