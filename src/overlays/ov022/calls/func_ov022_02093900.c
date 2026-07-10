extern int func_020358f4(unsigned int a, int b);
extern int func_020357f4(unsigned int a, int b);
extern void func_020357c8(unsigned int a, int b, int c);
extern int func_02030788(void);

void func_ov022_02093900(int param_1, int param_2) {
    int bVar1 = 0;
    int iVar5 = 0;
    do {
        if (func_020358f4(*(unsigned char *)(param_1 + 9), iVar5 + 1) != 0) {
            int iVar4;
            bVar1 = 1;
            iVar4 = func_020357f4(*(unsigned char *)(param_1 + 9), iVar5);
            func_020357c8(*(unsigned char *)(param_1 + 9), iVar5, param_2 + iVar4);
        }
        iVar5 = iVar5 + 1;
    } while (iVar5 < 0xf);
    if (func_02030788() != 0) {
        return;
    }
    if (bVar1 == 0) {
        return;
    }
    *(unsigned long long *)(param_1 + 0x46c) |= 0x20000000000LL;
}
