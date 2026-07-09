extern int func_020358f4(unsigned int arg0, int arg1);
int func_ov022_020ad7b0(int arg0) {
    int r = 0;
    int su = (int)((unsigned int)*(unsigned short *)(arg0 + 0x16) << 10);
    if (func_020358f4(*(unsigned char *)(arg0 + 9), 0x42) != 0) return r;
    if (*(unsigned short *)(arg0 + 0x12) <= (su >> 12)) r = 1;
    return r;
}
