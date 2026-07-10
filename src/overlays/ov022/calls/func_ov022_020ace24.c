extern int func_020358f4(int a, int b);
extern int func_ov022_020ad7b0(int obj);
extern void func_ov022_020acc94(int obj, int v);
extern int func_02030788(void);

void func_ov022_020ace24(int obj, unsigned int v, int mode) {
    int ok = 1;
    if (mode == 0 && func_020358f4(*(unsigned char *)(obj + 9), 0x41) != 0 &&
        func_ov022_020ad7b0(obj) != 0) {
        ok = 0;
    }
    if (ok == 0) return;
    if (mode != 0) func_ov022_020acc94(obj, v);
    else func_ov022_020acc94(obj, *(unsigned short *)(obj + 0x12) + v);
    if (func_02030788() != 0) return;
    *(unsigned long long *)(obj + 0x46c) |= 0x10000000000LL;
}
