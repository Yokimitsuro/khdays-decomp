extern void func_ov022_020acc94(unsigned int *arg0, int arg1);

void func_ov022_0209d0b0(unsigned int *arg0, int *arg1, int arg2) {
    int v;
    if (*(unsigned short *)((int)arg1 + 4) == 0) return;
    if ((unsigned int)(*(unsigned char *)((int)arg0 + 0x694) << 0x1c) >> 0x1f) return;
    v = *arg1 + arg2;
    *arg1 = v;
    if (v <= (int)((unsigned int)*(volatile unsigned short *)((int)arg1 + 4) << 0xc)) return;
    if (1 < *(unsigned short *)((int)arg0 + 0x12)) {
        func_ov022_020acc94(arg0, *(unsigned short *)((int)arg0 + 0x12) - 1);
    }
    *arg1 = 0;
}
