extern void func_01fff774(unsigned short *a, unsigned int b, unsigned int c);
extern int func_02030788(void);

void func_ov022_020acf14(unsigned int *param_1, unsigned int param_2) {
    func_01fff774((unsigned short *)(param_1[8] + 4), 0, param_2);
    param_1[0x1ec] = param_2;
    *(unsigned long long *)param_1 |= 0x20000000;
    if (func_02030788() == 0) {
        *(unsigned long long *)(param_1 + 0x119) |= 0x80000000;
    }
    if (func_02030788() != 0) {
        return;
    }
    *(unsigned long long *)(param_1 + 0x119) |= 0x2000000000LL;
}
