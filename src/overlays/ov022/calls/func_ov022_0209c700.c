extern int func_ov022_0209fc48(int a, int i);
extern void func_ov022_0209fb98(int a, int i, int one);

void func_ov022_0209c700(unsigned int *param_1) {
    int i = 0;
    char *p = (char *)param_1;
    do {
        if (*(char *)(p + 0xda9) != 0 && func_ov022_0209fc48((int)param_1, i) == 0) {
            func_ov022_0209fb98((int)param_1, i, 1);
        }
        i = i + 1;
        p = p + 0x164;
    } while (i < 2);
    *(unsigned long long *)param_1 |= 0x8000;
}
