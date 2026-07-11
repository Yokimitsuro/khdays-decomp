extern int func_02021980(void *a, int b);
extern void func_ov012_0205b214(int x, int y);

int func_ov012_0205b984(void *a, int b) {
    int r1 = func_02021980(a, b);
    int r2 = func_02021980(a, b + 8);
    func_ov012_0205b214(r1, r2);
    return 6;
}
