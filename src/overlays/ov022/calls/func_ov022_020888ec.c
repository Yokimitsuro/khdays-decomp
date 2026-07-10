extern int func_02030788(void);
extern int func_01fffde0(int a);

void func_ov022_020888ec(int param_1, int param_2) {
    unsigned int *puVar2;
    if (func_02030788() != 0) {
        return;
    }
    puVar2 = (unsigned int *)func_01fffde0(param_1);
    if (puVar2 == 0) {
        return;
    }
    if (param_2 != 0) {
        *(unsigned long long *)puVar2 |= 0x80;
        *(unsigned long long *)puVar2 |= 0x1000000;
        return;
    }
    *(unsigned long long *)puVar2 &= ~0x80LL;
    *(unsigned long long *)puVar2 &= ~0x1000000LL;
}
