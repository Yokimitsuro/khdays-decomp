extern void GX_LoadBGPltt();

int func_ov012_0205b3a4(int arg0, int arg1, int arg2) {
    int base = arg0 + (int)*(unsigned short *)(arg2 + 6) * 0xc;
    int t = ((int *)(base + 0x8000))[0x302];
    GX_LoadBGPltt(*(int *)(t + 0xc), 0, *(int *)(t + 8));
    return 1;
}
