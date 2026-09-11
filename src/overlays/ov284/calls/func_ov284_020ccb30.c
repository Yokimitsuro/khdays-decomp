extern unsigned int func_02023eb4(unsigned int range);
extern void func_0203c634(int *a, int i, int v);

typedef struct { unsigned char enabled : 1; } EnabledFlag;

void func_ov284_020ccb30(int param_1) {
    int child = *(int *)(param_1 + 4);
    int base, d;
    if (*(unsigned char *)*(int *)(child + 8) != 0) return;
    if (!((EnabledFlag *)(*(int *)child + 0x17a))->enabled) return;
    base = *(int *)(*(int *)child + 0x224);
    d = *(int *)(*(int *)child + 0x228) - base;
    if (d < 0) d = -d;
    *(int *)(child + 0x20) = base + func_02023eb4(d + 1);
    *(signed char *)(*(int *)child + 0x1c7) = 2;
    func_0203c634((int *)param_1, *(signed char *)(param_1 + 0x20), 0);
}
