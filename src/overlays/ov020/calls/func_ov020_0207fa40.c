extern int func_02021980(void *a, int b);
extern int func_02021948(void *a, int b);
extern int func_ov020_0207fc68(unsigned short a, int *b);
extern void func_ov002_0207643c(int a, int b);

int func_ov020_0207fa40(void *arg1, int arg2) {
    int r1 = func_02021980(arg1, arg2);
    int r2 = func_02021980(arg1, arg2 + 8);
    int local = func_02021948(arg1, arg2 + 0x10);
    int r = func_ov020_0207fc68((unsigned short)r2, &local);
    func_ov002_0207643c(r1, r);
    return 1;
}
