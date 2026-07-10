extern int func_ov022_02083f90(void);
extern int FX_Inv(int arg0, int arg1);

void func_ov022_020acebc(int arg0, int arg1) {
    volatile unsigned int *p = *(unsigned int **)(arg0 + 0x20);
    int inv;
    *p = (arg1 != 0x1000) ? (*p | 0x40) : (*p & ~0x40);
    inv = FX_Inv(func_ov022_02083f90(), 0x1000);
    *(int *)(arg0 + 0x458) = arg1;
    *(short *)(arg0 + 0x2aba) = (short)(((long long)inv * arg1 + 0x800) >> 0xc);
}
