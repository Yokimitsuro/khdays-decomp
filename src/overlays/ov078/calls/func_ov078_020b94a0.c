extern void func_02016b60(int a, int b, int c);
extern void func_ov022_02091eb0(int e);

void func_ov078_020b94a0(int self) {
    int i;
    for (i = 0; i < (int)*(unsigned char *)(self + 0x19); i++) {
        int e = *(int *)(self + 0xc) + i * 0x1c8;
        int t = *(signed char *)(e + 2);
        if (t != 0 && t != 3) {
            func_02016b60(*(int *)(e + 0xa0), 6, 0x14 - i);
            func_ov022_02091eb0(e);
        }
    }
}
