extern int func_ov022_02093a1c(int arg0);
extern void func_ov022_0209398c(int arg0, int arg1);

void func_ov022_02093c48(int arg0, int arg1, int arg2, int arg3) {
    if (*(unsigned char *)(arg0 + 1) != 0 && *(unsigned char *)(arg0 + 1) != 4) return;
    *(short *)(arg0 + 0x10) = (short)arg1;
    *(int *)(arg0 + 0x14) = arg2;
    *(int *)(arg0 + 0x18) = arg3;
    *(int *)(arg0 + 0x4d0) = 0;
    if (*(int *)(arg0 + 0x14) != 0xd && 2 <= arg1 && arg1 < 0xc) {
        func_ov022_0209398c(arg0, func_ov022_02093a1c((int)*(short *)(arg0 + 0x10)));
    }
    *(unsigned char *)(arg0 + 1) = 1;
}
