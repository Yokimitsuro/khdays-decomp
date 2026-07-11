extern int func_02021948(void *a, void *b);
extern void func_ov012_0205b0cc(int x);

int func_ov012_0205b940(void *arg1, char *arg2) {
    int v = 0;
    if (*(short *)(arg2 + 0) == 2) {
        v = func_02021948(arg1, arg2);
    }
    if (*(short *)(arg2 + 8) == 2) {
        func_02021948(arg1, arg2 + 8);
    }
    if (*(short *)(arg2 + 0x10) == 2) {
        func_02021948(arg1, arg2 + 0x10);
    }
    func_ov012_0205b0cc(v);
    return 1;
}
