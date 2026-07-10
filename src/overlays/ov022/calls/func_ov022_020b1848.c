extern int func_ov022_020b1510(unsigned char *p);
extern void func_ov022_020b18f8(unsigned int *a, int b, unsigned int c, unsigned int d);
extern void func_ov022_020b1730(unsigned int *a, int b);

int func_ov022_020b1848(unsigned int *param_1, int param_2, int param_3, int param_4) {
    unsigned int uVar2;
    unsigned int uVar3;
    if (func_ov022_020b1510((unsigned char *)*param_1) == 0) {
        return 0;
    }
    if (*(char *)((int)param_1 + 0xb) == -1) {
        uVar3 = *(unsigned char *)((int)param_1 + 9) & 0xfffffffe;
        uVar2 = (unsigned char)uVar3 | 2;
        *(char *)((int)param_1 + 9) = (char)uVar2;
        *(char *)((int)param_1 + 8) = 0;
        func_ov022_020b18f8(param_1, *(char *)((int)param_1 + 10), uVar2, uVar3);
        *(char *)((int)param_1 + 8) = 3;
        return 1;
    }
    *(char *)((int)param_1 + 10) = *(char *)((int)param_1 + 0xb);
    *(char *)((int)param_1 + 0xb) = -1;
    *(char *)((int)param_1 + 8) = 0;
    func_ov022_020b1730(param_1, 0);
    return 0;
}
